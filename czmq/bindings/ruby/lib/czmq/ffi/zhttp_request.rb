################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################

module CZMQ
  module FFI

    # Http request that can be received from zhttp_server or sent to zhttp_client.
    # Class can be reused between send & recv calls.
    # Headers and Content is being destroyed after every send call.
    # @note This class is 100% generated using zproject.
    class ZhttpRequest
      # Raised when one tries to use an instance of {ZhttpRequest} after
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
          ::CZMQ::FFI.zhttp_request_destroy ptr_ptr
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

      # Create a new http request.
      # @return [CZMQ::ZhttpRequest]
      def self.new()
        ptr = ::CZMQ::FFI.zhttp_request_new()
        __new ptr
      end

      # Destroy an http request.
      #
      # @return [void]
      def destroy()
        return unless @ptr
        self_p = __ptr_give_ref
        result = ::CZMQ::FFI.zhttp_request_destroy(self_p)
        result
      end

      # Receive a new request from zhttp_server.
      # Return the underlying connection if successful, to be used when calling zhttp_response_send.
      #
      # @param sock [Zsock, #__ptr]
      # @return [::FFI::Pointer]
      def recv(sock)
        raise DestroyedError unless @ptr
        self_p = @ptr
        sock = sock.__ptr if sock
        result = ::CZMQ::FFI.zhttp_request_recv(self_p, sock)
        result
      end

      # Send a request to zhttp_client.
      # Url and the request path will be concatenated.
      # This behavior is useful for url rewrite and reverse proxy.
      #
      # Send also allow two user provided arguments which will be returned with the response.
      # The reason for two, is to be able to pass around the server connection when forwarding requests or both a callback function and an arg.
      #
      # @param client [ZhttpClient, #__ptr]
      # @param timeout [Integer, #to_int, #to_i]
      # @param arg [::FFI::Pointer, #to_ptr]
      # @param arg2 [::FFI::Pointer, #to_ptr]
      # @return [Integer]
      def send(client, timeout, arg, arg2)
        raise DestroyedError unless @ptr
        self_p = @ptr
        client = client.__ptr if client
        timeout = Integer(timeout)
        result = ::CZMQ::FFI.zhttp_request_send(self_p, client, timeout, arg, arg2)
        result
      end

      # Get the request method
      #
      # @return [String]
      def method()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_method(self_p)
        result
      end

      # Set the request method
      #
      # @param method [String, #to_s, nil]
      # @return [void]
      def set_method(method)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_set_method(self_p, method)
        result
      end

      # Get the request url.
      # When receiving a request from http server this is only the path part of the url.
      #
      # @return [String]
      def url()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_url(self_p)
        result
      end

      # Set the request url
      # When sending a request to http client this should be full url.
      #
      # @param url [String, #to_s, nil]
      # @return [void]
      def set_url(url)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_set_url(self_p, url)
        result
      end

      # Get the request content type
      #
      # @return [String]
      def content_type()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_content_type(self_p)
        result
      end

      # Set the request content type
      #
      # @param content_type [String, #to_s, nil]
      # @return [void]
      def set_content_type(content_type)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_set_content_type(self_p, content_type)
        result
      end

      # Get the content length of the request
      #
      # @return [Integer]
      def content_length()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_content_length(self_p)
        result
      end

      # Get the headers of the request
      #
      # @return [Zhash]
      def headers()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_headers(self_p)
        result = Zhash.__new result, false
        result
      end

      # Get the content of the request.
      #
      # @return [String]
      def content()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_content(self_p)
        result
      end

      # Get the content of the request.
      #
      # @return [::FFI::AutoPointer]
      def get_content()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_get_content(self_p)
        result = ::FFI::AutoPointer.new(result, LibC.method(:free))
        result
      end

      # Set the content of the request.
      # Content must by dynamically allocated string.
      # Takes ownership of the content.
      #
      # @param content [::FFI::Pointer, #to_ptr]
      # @return [void]
      def set_content(content)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_set_content(self_p, content)
        result
      end

      # Set the content of the request..
      # The content is assumed to be constant-memory and will therefore not be copied or deallocated in any way.
      #
      # @param content [String, #to_s, nil]
      # @return [void]
      def set_content_const(content)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_set_content_const(self_p, content)
        result
      end

      # Set the content to NULL
      #
      # @return [void]
      def reset_content()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_reset_content(self_p)
        result
      end

      # Match the path of the request.
      # Support wildcards with '%s' symbol inside the match string.
      # Matching wildcards until the next '/', '?' or '\0'.
      # On successful match the variadic arguments will be filled with the matching strings.
      # On successful match the method is modifying the url field and break it into substrings.
      # If you need to use the url, do it before matching or take a copy.
      #
      # User must not free the variadic arguments as they are part of the url.
      #
      # To use the percent symbol, just double it, e.g "%%something".
      #
      # Example:
      # if (zhttp_request_match (request, "POST", "/send/%s/%s", &name, &id))
      #
      # @param method [String, #to_s, nil]
      # @param path [String, #to_s, nil]
      # @param args [Array<Object>] see https://github.com/ffi/ffi/wiki/examples#using-varargs
      # @return [Boolean]
      def match(method, path, *args)
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::CZMQ::FFI.zhttp_request_match(self_p, method, path, *args)
        result
      end

      # Self test of this class.
      #
      # @param verbose [Boolean]
      # @return [void]
      def self.test(verbose)
        verbose = !(0==verbose||!verbose) # boolean
        result = ::CZMQ::FFI.zhttp_request_test(verbose)
        result
      end
    end
  end
end

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################