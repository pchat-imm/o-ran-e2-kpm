/*
 *
 * Copyright 2021-2023 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "pseudo_random_generator_impl.h"
#include "pseudo_random_generator_sequence.h"
#include "srsran/support/math_utils.h"
#include "srsran/support/srsran_assert.h"

#if __SSE3__
#include <immintrin.h>
#endif // __SSE3__

#ifdef __aarch64__
#include <arm_neon.h>
#endif // __aarch64__

using namespace srsran;

const pseudo_random_generator_impl::x1_init_s pseudo_random_generator_impl::x1_init =
    pseudo_random_generator_impl::x1_init_s();

const pseudo_random_generator_impl::x2_init_s pseudo_random_generator_impl::x2_init =
    pseudo_random_generator_impl::x2_init_s();

pseudo_random_generator_impl::x1_init_s::x1_init_s() : x1(1)
{
  pseudo_random_generator_sequence sequence(1, 0);
  // Compute transition step.
  for (uint32_t n = 0; n != SEQUENCE_NC; ++n) {
    sequence.step(1);
  }
  x1 = sequence.get_x1();
}

unsigned pseudo_random_generator_impl::x1_init_s::get() const
{
  return x1;
}

pseudo_random_generator_impl::x2_init_s::x2_init_s() : x2()
{
  // For each bit of the seed.
  for (uint32_t i = 0; i != SEQUENCE_SEED_LEN; ++i) {
    // Compute transition step.
    pseudo_random_generator_sequence sequence(0, 1 << i);
    for (uint32_t n = 0; n != SEQUENCE_NC; ++n) {
      sequence.step(1);
    }
    x2[i] = sequence.get_x2();
  }
}

unsigned pseudo_random_generator_impl::x2_init_s::get(unsigned c_init) const
{
  unsigned ret = 0;

  for (unsigned i = 0; i != SEQUENCE_SEED_LEN; ++i) {
    if ((c_init >> i) & 1UL) {
      ret ^= x2[i];
    }
  }

  return ret;
}

void pseudo_random_generator_impl::init(unsigned c_init)
{
  x1 = x1_init.get();
  x2 = x2_init.get(c_init);
}

void pseudo_random_generator_impl::init(const state_s& state)
{
  x1 = state.x1;
  x2 = state.x2;
}

void pseudo_random_generator_impl::advance(unsigned count)
{
  unsigned i = 0;

  static constexpr unsigned max_step_size = pseudo_random_generator_sequence::get_max_step_size();

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  // Advance sequence states with the maximum parallel bits.
  for (unsigned i_end = (count / max_step_size) * max_step_size; i != i_end; i += max_step_size) {
    sequence.step<max_step_size>();
  }

  // Advance the remainder in a smaller step.
  unsigned remainder = count % max_step_size;
  if (remainder != 0) {
    sequence.step(remainder);
  }

  // Update x1 and x2 states.
  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

void pseudo_random_generator_impl::generate(bit_buffer& data)
{
  // Number of bits per processing word.
  static constexpr unsigned nof_bits_per_byte = 8;

  // Calculate the maximum number of simultaneous words to process.
  static constexpr unsigned max_nof_bytes_step =
      pseudo_random_generator_sequence::get_max_step_size() / nof_bits_per_byte;

  // Calculate the maximum number of simultaneous bits to process.
  static constexpr unsigned max_nof_bits_step = max_nof_bytes_step * nof_bits_per_byte;

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  // Processes batches of 24 bits in parallel.
  for (unsigned i_byte = 0, i_byte_end = (data.size() / max_nof_bits_step) * max_nof_bytes_step;
       i_byte != i_byte_end;) {
    uint32_t c = sequence.step(max_nof_bits_step);

    // Processes each byte of the batch.
    for (unsigned i_byte_batch = 0; i_byte_batch != max_nof_bytes_step; ++i_byte, ++i_byte_batch) {
      // Calculate the output byte.
      uint8_t output_byte = reverse_byte(static_cast<uint8_t>(c & mask_lsb_ones<uint32_t>(nof_bits_per_byte)));

      // Insert the output byte.
      data.set_byte(output_byte, i_byte);

      // Advance sequence one byte.
      c = c >> nof_bits_per_byte;
    }
  }

  // Process spare bits in a batch of the remainder bits.
  unsigned i_bit     = (data.size() / max_nof_bits_step) * max_nof_bits_step;
  unsigned remainder = data.size() - i_bit;
  uint32_t c         = sequence.step(remainder);

  while (remainder != 0) {
    // Process per byte basis, ceiling at the remainder.
    unsigned word_size = std::min(remainder, nof_bits_per_byte);

    // Mask the LSB of the sequence.
    uint32_t mask = mask_lsb_ones<uint32_t>(nof_bits_per_byte);

    // Shift to align the reversed sequence LSB with the remainder bits.
    unsigned right_shift = nof_bits_per_byte - word_size;

    // Calculate the output byte.
    uint8_t output_word = (reverse_byte(static_cast<uint8_t>(c & mask)) >> right_shift);

    // Insert the output byte.
    data.insert(output_word, i_bit, word_size);

    // Advance sequence.
    c = c >> word_size;

    // Advance bit index.
    i_bit += word_size;

    // Decrement remainder.
    remainder -= word_size;
  }

  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

#define FLOAT_U32_XOR(DST, SRC, U32_MASK)                                                                              \
  do {                                                                                                                 \
    uint32_t temp_u32;                                                                                                 \
    memcpy(&temp_u32, &(SRC), 4);                                                                                      \
    temp_u32 ^= (U32_MASK);                                                                                            \
    memcpy(&(DST), &temp_u32, 4);                                                                                      \
  } while (false)

void pseudo_random_generator_impl::generate(span<float> out, float value)
{
  uint32_t i      = 0;
  unsigned length = out.size();

  // Number of bits that can be processed with a SIMD register.
  static constexpr unsigned nof_bits_per_simd = 4;

  // Calculate maximum number of SIMD words that can be generated in parallel.
  static constexpr unsigned max_nof_word_step =
      pseudo_random_generator_sequence::get_max_step_size() / nof_bits_per_simd;

  // Calculate the number of bits for sequence step.
  static constexpr unsigned max_nof_bits_step = max_nof_word_step * nof_bits_per_simd;

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  // Process in batches of max_nof_bits_step bits.
  for (unsigned i_end = (length / max_nof_bits_step) * max_nof_bits_step; i != i_end; i += max_nof_bits_step) {
    uint32_t c = sequence.step<max_nof_bits_step>();

    uint32_t j = 0;
#ifdef __SSE3__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 4 LSB.
      __m128i mask = _mm_set1_epi32(c >> j);

      // Masks each bit.
      mask = _mm_and_si128(mask, _mm_setr_epi32(1, 2, 4, 8));

      // Get non zero mask.
      mask = _mm_cmpgt_epi32(mask, _mm_set1_epi32(0));

      // And with MSB.
      mask = _mm_and_si128(mask, (__m128i)_mm_set1_ps(-0.0F));

      // Load input.
      __m128 v = _mm_set1_ps(value);

      // Loads input and perform sign XOR.
      v = _mm_xor_ps((__m128)mask, v);

      _mm_storeu_ps(&out[i + j], v);
    }
#endif // __SSE3__
#ifdef __aarch64__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 4 LSB.
      int32x4_t mask_s32 = vdupq_n_s32(c >> j);

      // Masks each bit.
      const int32x4_t tmp_mask = vcombine_s32(vcreate_s32(1ULL | (2ULL << 32)), vcreate_s32(4ULL | (8ULL << 32)));

      mask_s32 = vandq_s32(mask_s32, tmp_mask);

      // Get non zero mask.
      uint32x4_t mask_u32 = vcgtq_s32(mask_s32, vdupq_n_s32(0));

      // And with MSB.
      mask_s32 = vandq_s32(vreinterpretq_s32_u32(mask_u32), vreinterpretq_s32_f32(vdupq_n_f32(-0.0F)));

      // Load input.
      float32x4_t v = vdupq_n_f32(value);

      // Loads input and perform sign XOR.
      v = vreinterpretq_f32_s32(veorq_s32(mask_s32, vreinterpretq_s32_f32(v)));

      vst1q_f32(&out[i + j], v);
    }
#endif // __aarch64__

    // Finish the parallel bits with generic code.
    for (; j != max_nof_bits_step; ++j) {
      FLOAT_U32_XOR(out[i + j], value, (c << (31U - j)) & 0x80000000);
    }
  }

  unsigned remainder = length - i;
  uint32_t c         = sequence.step(remainder);
  for (; i != length; ++i) {
    FLOAT_U32_XOR(out[i], value, c << 31U);

    c = c >> 1U;
  }

  // Update x1 and x2 states.
  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

void pseudo_random_generator_impl::apply_xor(bit_buffer& out, const bit_buffer& in)
{
  srsran_assert(in.size() == out.size(),
                "Input size (i.e., {}) and output size (i.e., {}) must be equal.",
                in.size(),
                out.size());

  // Number of bits per processing word.
  static constexpr unsigned nof_bits_per_byte = 8;

  // Calculate the maximum number of simultaneous words to process.
  static constexpr unsigned max_nof_bytes_step =
      pseudo_random_generator_sequence::get_max_step_size() / nof_bits_per_byte;

  // Calculate the maximum number of simultaneous bits to process.
  static constexpr unsigned max_nof_bits_step = max_nof_bytes_step * nof_bits_per_byte;

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  // Processes batches of words.
  for (unsigned i_byte = 0, i_byte_end = (in.size() / max_nof_bits_step) * max_nof_bytes_step; i_byte != i_byte_end;) {
    uint32_t c = sequence.step<max_nof_bits_step>();

    // Processes each byte of the batch.
    for (unsigned i_byte_batch = 0; i_byte_batch != max_nof_bytes_step; ++i_byte, ++i_byte_batch) {
      // Extract input byte.
      uint8_t input_byte = in.get_byte(i_byte);

      // Calculate the output byte.
      uint8_t output_byte = input_byte ^ reverse_byte(static_cast<uint8_t>(c & 0xff));

      // Insert the output byte.
      out.set_byte(output_byte, i_byte);

      // Advance sequence one byte.
      c = c >> nof_bits_per_byte;
    }
  }

  // Process spare bits in a batch of the remainder bits.
  unsigned i_bit     = (in.size() / max_nof_bits_step) * max_nof_bits_step;
  unsigned remainder = in.size() - i_bit;

  uint32_t c = sequence.step(remainder);

  // Process bits.
  while (remainder != 0) {
    // Process per byte basis, ceiling at the remainder.
    unsigned word_size = std::min(remainder, nof_bits_per_byte);

    uint8_t input_word = in.extract(i_bit, word_size);

    // Shift to align the reversed sequence LSB with the remainder bits.
    unsigned right_shift = nof_bits_per_byte - word_size;

    // Calculate the output byte.
    uint8_t output_word = input_word ^ (reverse_byte(static_cast<uint8_t>(c & 0xff)) >> right_shift);

    // Insert the output byte.
    out.insert(output_word, i_bit, word_size);

    // Advance sequence.
    c = c >> word_size;

    // Advance bit index.
    i_bit += word_size;

    // Decrement remainder.
    remainder -= word_size;
  }

  // Update x1 and x2 states.
  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

void pseudo_random_generator_impl::apply_xor(span<uint8_t> out, span<const uint8_t> in)
{
  srsran_assert(in.size() == out.size(),
                "Input size (i.e., {}) and output size (i.e., {}) must be equal.",
                in.size(),
                out.size());

  // Number of bits that can be processed with a SIMD register.
  static constexpr unsigned nof_bits_per_simd = 16;

  // Calculate maximum number of SIMD words that can be generated in parallel.
  static constexpr unsigned max_nof_word_step =
      pseudo_random_generator_sequence::get_max_step_size() / nof_bits_per_simd;

  // Calculate the number of bits for sequence step.
  static constexpr unsigned max_nof_bits_step = max_nof_word_step * nof_bits_per_simd;

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  unsigned i      = 0;
  unsigned length = in.size();

  for (unsigned i_end = (length / max_nof_bits_step) * max_nof_bits_step; i != i_end; i += max_nof_bits_step) {
    uint32_t c = sequence.step<max_nof_bits_step>();

    unsigned j = 0;
#ifdef __SSE3__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 16 LSB
      __m128i mask = _mm_set1_epi32(c);
      mask         = _mm_shuffle_epi8(mask, _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1));

      // Masks each bit.
      mask = _mm_and_si128(mask, _mm_set_epi64x(0x8040201008040201, 0x8040201008040201));

      // Get non zero mask.
      mask = _mm_cmpeq_epi8(mask, _mm_set_epi64x(0x8040201008040201, 0x8040201008040201));

      // Reduce to 1s and 0s.
      mask = _mm_and_si128(mask, _mm_set1_epi8(1));

      // Load input.
      __m128i v = _mm_loadu_si128((__m128i*)(&in[i + j]));

      // Apply XOR.
      v = _mm_xor_si128(mask, v);

      // Store output.
      _mm_storeu_si128((__m128i*)(&out[i + j]), v);
    }
#endif // __SSE3__
#ifdef __aarch64__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 16 LSB.
      uint32x2_t c_dup_u32 = vdup_n_u32(c);
      uint8x16_t mask_u8 =
          vcombine_u8(vdup_lane_u8(vreinterpret_u8_u32(c_dup_u32), 0), vdup_lane_u8(vreinterpret_u8_u32(c_dup_u32), 1));

      // Create bit masks.
      const uint8_t    bit_masks[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
      const uint8x16_t bit_masks_u8 = vcombine_u8(vcreate_u8(*(reinterpret_cast<const uint64_t*>(bit_masks))),
                                                  vcreate_u8(*(reinterpret_cast<const uint64_t*>(bit_masks))));
      // Mask each bit.
      mask_u8 = vandq_u8(mask_u8, bit_masks_u8);

      // Get non zero mask.
      mask_u8 = vceqq_u8(mask_u8, bit_masks_u8);

      // Reduce to 1s and 0s.
      mask_u8 = vandq_u8(mask_u8, vdupq_n_u8(1));

      // Load input.
      uint8x16_t v = vld1q_u8(&in[i + j]);

      // Apply XOR.
      v = veorq_u8(mask_u8, v);

      // Store output.
      vst1q_u8(&out[i + j], v);
    }
#endif // __aarch64__

    // Apply mask to remainder bits.
    for (; j != max_nof_bits_step; ++j) {
      out[i + j] = in[i + j] ^ (c & 1U);
      c          = c >> 1U;
    }
  }

  // Apply remainder bits.
  unsigned remainder = length - i;
  uint32_t c         = sequence.step(remainder);
  for (; i != length; ++i) {
    out[i] = in[i] ^ (c & 1U);
    c      = c >> 1U;
  }

  // Update x1 and x2 states.
  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

void pseudo_random_generator_impl::apply_xor(span<log_likelihood_ratio> out, span<const log_likelihood_ratio> in)
{
  srsran_assert(in.size() == out.size(),
                "Input size (i.e., {}) and output size (i.e., {}) must be equal.",
                in.size(),
                out.size());

  unsigned i      = 0;
  unsigned length = in.size();

  // Number of bits that can be processed with a SIMD register.
  static constexpr unsigned nof_bits_per_simd = 16;

  // Calculate maximum number of SIMD words that can be generated in parallel.
  static constexpr unsigned max_nof_word_step =
      pseudo_random_generator_sequence::get_max_step_size() / nof_bits_per_simd;

  // Calculate the number of bits for sequence step.
  static constexpr unsigned max_nof_bits_step = max_nof_word_step * nof_bits_per_simd;

  // Create sequence with the current x1 and x2 states.
  pseudo_random_generator_sequence sequence(x1, x2);

  for (unsigned i_end = (length / max_nof_bits_step) * max_nof_bits_step; i != i_end; i += max_nof_bits_step) {
    uint32_t c = sequence.step<max_nof_bits_step>();

    unsigned j = 0;
#ifdef __SSE3__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 16 LSB.
      __m128i mask = _mm_set1_epi32(c);
      mask         = _mm_shuffle_epi8(mask, _mm_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1));

      // Masks each bit.
      mask = _mm_and_si128(mask, _mm_set_epi64x(0x8040201008040201, 0x8040201008040201));

      // Get non zero mask.
      mask = _mm_cmpeq_epi8(mask, _mm_set_epi64x(0x8040201008040201, 0x8040201008040201));

      // Load input.
      __m128i v = _mm_loadu_si128((__m128i*)(&in[i + j]));

      // Negate.
      v = _mm_xor_si128(mask, v);

      // Add one.
      mask = _mm_and_si128(mask, _mm_set1_epi8(1));
      v    = _mm_add_epi8(v, mask);

      _mm_storeu_si128((__m128i*)(&out[i + j]), v);
    }
#endif // __SSE3__
#ifdef __aarch64__
    for (; j != max_nof_bits_step; j += nof_bits_per_simd) {
      // Preloads bits of interest in the 16 LSB.
      uint32x2_t c_dup_u32 = vdup_n_u32(c);
      uint8x16_t mask_u8 =
          vcombine_u8(vdup_lane_u8(vreinterpret_u8_u32(c_dup_u32), 0), vdup_lane_u8(vreinterpret_u8_u32(c_dup_u32), 1));

      // Create bit masks.
      const uint8_t    bit_masks[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
      const uint8x16_t bit_masks_u8 = vcombine_u8(vcreate_u8(*(reinterpret_cast<const uint64_t*>(bit_masks))),
                                                  vcreate_u8(*(reinterpret_cast<const uint64_t*>(bit_masks))));
      // Mask each bit.
      mask_u8 = vandq_u8(mask_u8, bit_masks_u8);

      // Get non zero mask.
      mask_u8 = vceqq_u8(mask_u8, bit_masks_u8);

      // Load input.
      int8x16_t v = vld1q_s8(reinterpret_cast<const int8_t*>(&in[i + j]));

      // Negate.
      v = veorq_s8(vreinterpretq_s8_u8(mask_u8), v);

      // Add one.
      int8x16_t one_s8 = vandq_s8(vreinterpretq_s8_u8(mask_u8), vdupq_n_s8(1));
      v                = vaddq_s8(v, one_s8);

      // Store the result.
      vst1q_s8(reinterpret_cast<int8_t*>(&out[i + j]), v);
    }
#endif // __aarch64__
    for (; j != max_nof_bits_step; ++j) {
      out[i + j] = in[i + j].to_value_type() * (((c >> j) & 1U) ? -1 : +1);
    }
  }

  // Apply remainder bits.
  unsigned remainder = length - i;
  uint32_t c         = sequence.step(remainder);
  for (; i != length; ++i) {
    out[i] = in[i].to_value_type() * ((c & 1U) ? -1 : 1);

    c = c >> 1;
  }

  // Update x1 and x2 states.
  x1 = sequence.get_x1();
  x2 = sequence.get_x2();
}

pseudo_random_generator::state_s pseudo_random_generator_impl::get_state() const
{
  return {x1, x2};
}
