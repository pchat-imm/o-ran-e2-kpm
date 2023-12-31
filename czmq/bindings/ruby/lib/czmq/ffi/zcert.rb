################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################

module CZMQ
  module FFI

    # work with CURVE security certificates
    # @note This class is 100% generated using zproject.
    class Zcert
      # Raised when one tries to use an instance of {Zcert} after
      # the internal pointer to the native object has been nullified.
      class DestroyedError < RuntimeError; end

      # Boilerplate for self pointer, initializer, and finalizer
      class << self
        alias :__new :new
      end
      # Attaches the pointer _ptr_ to this instance and defines a finalizer for
      # it if necessary.
      # @param ptr [::FFI::Pointer]
      # @param finalize [Boolean]
      def initialize(ptr, finalize = true)
        @ptr = ptr
        if @ptr.null?
          @ptr = nil # Remove null pointers so we don't have to test for them.
        elsif finalize
          @finalizer = self.class.create_finalizer_for @ptr
          ObjectSpace.define_finalizer self, @finalizer
        end
      end
      # @param ptr [::FFI::Pointer]
      # @return [Proc]
      def self.create_finalizer_for(ptr)
        ptr_ptr = ::FFI::MemoryPointer.new :pointer

        Proc.new do
          ptr_ptr.write_pointer ptr
          ::CZMQ::FFI.zcert_destroy ptr_ptr
        end
      end
      # @return [Boolean]
      def null?
        !@ptr or @ptr.null?
      end
      # Return internal pointer
      # @return [::FFI::Pointer]
      def __ptr
        raise DestroyedError unless @ptr
        @ptr
      end
      # So external Libraries can just pass the Object to a FFI function which expects a :pointer
      alias_method :to_ptr, :__ptr
      # Nullify internal pointer and return pointer pointer.
      # @note This detaches the current instance from the native object
      #   and thus makes it unusable.
      # @return [::FFI::MemoryPointer] the pointer pointing to a pointer
      #   pointing to the native object
      def __ptr_give_ref
        raise DestroyedError unless @ptr
        ptr_ptr = ::FFI::MemoryPointer.new :pointer
        ptr_ptr.write_pointer @ptr
        __undef_finalizer if @finalizer
        @ptr = nil
        ptr_ptr
      end
      # Undefines the finalizer for this object.
      # @note Only use this if you need to and can guarantee that the native
      #   object will be freed by other means.
      # @return [void]
      def __undef_finalizer
        ObjectSpace.undefine_finalizer self
        @finalizer = nil
      end

      # Create and initialize a new certificate in memory
      # @return [CZMQ::Zcert]
      def self.new()
        ptr = ::CZMQ::FFI.zcert_new()
        __new ptr
      end

      # Accepts public/secret key pair from caller
      # @param public_key [::FFI::Pointer, #to_ptr]
      # @param secret_key [::FFI::Pointer, #to_ptr]
      # @return [CZMQ::Zcert]
      def self.new_from(public_key, secret_key)
        ptr = ::CZMQ::FFI.zcert_new_from(public_key, secret_key)
        __new ptr
      end

      # Accepts public/secret key text pair from caller
      # @param public_txt [String, #to_s, nil]
      # @param secret_txt [String, #to_s, nil]
      # @return [CZMQ::Zcert]
      def self.new_from_txt(public_txt, secret_txt)
        ptr = ::CZMQ::FFI.zcert_new_from_txt(public_txt, secret_txt)
        __new ptr
      end

      # Load certificate from file
      # @param filename [String, #to_s, nil]
      # @return [CZMQ::Zcert]
      def self.load(filename)
        ptr = ::CZMQ::FFI.zcert_load(filename)
        __new ptr
      end

      # Destroy a certificate in memory
      #
      # @return [void]
      def destroy()
        return unless @ptr
        self_p = __ptr_give_ref
        result = ::CZMQ::FFI.zcert_destroy(self_p)
        result
      end

      # Return public part of key pair as 32-byte binary string
      #
      # @return [::FFI::Pointer]
      def public_key()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_public_key(self_p)
        result
      end

      # Return secret part of key pair as 32-byte binary string
      #
      # @return [::FFI::Pointer]
      def secret_key()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_secret_key(self_p)
        result
      end

      # Return public part of key pair as Z85 armored string
      #
      # @return [String]
      def public_txt()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_public_txt(self_p)
        result
      end

      # Return secret part of key pair as Z85 armored string
      #
      # @return [String]
      def secret_txt()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_secret_txt(self_p)
        result
      end

      # Set certificate metadata from formatted string.
      #
      # @param name [String, #to_s, nil]
      # @param format [String, #to_s, nil]
      # @param args [Array<Object>] see https://github.com/ffi/ffi/wiki/examples#using-varargs
      # @return [void]
      def set_meta(name, format, *args)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_set_meta(self_p, name, format, *args)
        result
      end

      # Unset certificate metadata.
      #
      # @param name [String, #to_s, nil]
      # @return [void]
      def unset_meta(name)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_unset_meta(self_p, name)
        result
      end

      # Get metadata value from certificate; if the metadata value doesn't
      # exist, returns NULL.
      #
      # @param name [String, #to_s, nil]
      # @return [String]
      def meta(name)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_meta(self_p, name)
        result
      end

      # Get list of metadata fields from certificate. Caller is responsible for
      # destroying list. Caller should not modify the values of list items.
      #
      # @return [Zlist]
      def meta_keys()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_meta_keys(self_p)
        result = Zlist.__new result, false
        result
      end

      # Save full certificate (public + secret) to file for persistent storage
      # This creates one public file and one secret file (filename + "_secret").
      #
      # @param filename [String, #to_s, nil]
      # @return [Integer]
      def save(filename)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_save(self_p, filename)
        result
      end

      # Save public certificate only to file for persistent storage
      #
      # @param filename [String, #to_s, nil]
      # @return [Integer]
      def save_public(filename)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_save_public(self_p, filename)
        result
      end

      # Save secret certificate only to file for persistent storage
      #
      # @param filename [String, #to_s, nil]
      # @return [Integer]
      def save_secret(filename)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_save_secret(self_p, filename)
        result
      end

      # Apply certificate to socket, i.e. use for CURVE security on socket.
      # If certificate was loaded from public file, the secret key will be
      # undefined, and this certificate will not work successfully.
      #
      # @param socket [::FFI::Pointer, #to_ptr]
      # @return [void]
      def apply(socket)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_apply(self_p, socket)
        result
      end

      # Return copy of certificate; if certificate is NULL or we exhausted
      # heap memory, returns NULL.
      #
      # @return [Zcert]
      def dup()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_dup(self_p)
        result = Zcert.__new result, true
        result
      end

      # Return true if two certificates have the same keys
      #
      # @param compare [Zcert, #__ptr]
      # @return [Boolean]
      def eq(compare)
        raise DestroyedError unless @ptr
        self_p = @ptr
        compare = compare.__ptr if compare
        result = ::CZMQ::FFI.zcert_eq(self_p, compare)
        result
      end

      # Print certificate contents to stdout
      #
      # @return [void]
      def print()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zcert_print(self_p)
        result
      end

      # Self test of this class
      #
      # @param verbose [Boolean]
      # @return [void]
      def self.test(verbose)
        verbose = !(0==verbose||!verbose) # boolean
        result = ::CZMQ::FFI.zcert_test(verbose)
        result
      end
    end
  end
end

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
