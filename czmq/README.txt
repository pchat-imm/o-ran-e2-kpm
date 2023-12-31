.set GIT=https://github.com/zeromq/czmq
.sub 0MQ=ØMQ

[![GitHub release](https://img.shields.io/github/release/zeromq/czmq.svg)](https://github.com/zeromq/czmq/releases)
[![OBS draft](https://img.shields.io/badge/OBS%20master-draft-yellow.svg)](http://software.opensuse.org/download.html?project=network%3Amessaging%3Azeromq%3Agit-draft&package=czmq)
[![OBS stable](https://img.shields.io/badge/OBS%20master-stable-yellow.svg)](http://software.opensuse.org/download.html?project=network%3Amessaging%3Azeromq%3Agit-stable&package=czmq)
<a target="_blank" href="http://webchat.freenode.net?channels=%23zeromq&uio=d4"><img src="https://cloud.githubusercontent.com/assets/493242/14886493/5c660ea2-0d51-11e6-8249-502e6c71e9f2.png" height = "20" /></a>
[![license](https://img.shields.io/badge/license-MPL%202.0-green.svg)](https://github.com/zeromq/czmq/blob/master/LICENSE)

# CZMQ - High-level C binding for 0MQ

| Linux & MacOSX | Windows  |
|:--------------:|:--------:|
|[![Build Status](https://travis-ci.org/zeromq/czmq.png?branch=master)](https://travis-ci.org/zeromq/czmq)|[![Build status](https://ci.appveyor.com/api/projects/status/q7y22juu3pnl5wq6?svg=true)](https://ci.appveyor.com/project/zeromq/czmq)|

## Contents

.toc 3

## Overview

### Scope and Goals

CZMQ has these goals:

* To wrap the 0MQ core API in semantics that lead to shorter, more readable applications.
* To hide as far as possible the differences between different versions of 0MQ (2.x, 3.x, 4.x).
* To provide a space for development of more sophisticated API semantics.
* To wrap the 0MQ security features with high-level tools and APIs.
* To become the basis for other language bindings built on top of CZMQ.

CZMQ grew out of concepts developed in [ØMQ - The Guide](http://zguide.zeromq.org).

[diagram]
                              +---------------+
                              |               |
                              | C application |
                              |               |
                              +-----+---+-----+
                                    |   |
                                    |   |
                       +------------+   |
                       |                |
                       v                |
  Open context    +---------+           |
  Create sockets  |         |           |    Connect, bind sockets
  Close sockets   |  CZMQ   |           |    get/set socket options
  Send/receive    |    cYEL |           |
  Multithreading  +----+----+           |
  Reactor pattern      |                |
  Hash container       +------------+   |
  List container                    |   |
  System clock                      v   v
  Close context                  +---------+
                                 |         |
                                 | libzmq  |
                                 |         |
                                 +---------+

[/diagram]

### Ownership and License

The contributors are listed in AUTHORS. This project uses the MPL v2 license, see LICENSE.

CZMQ uses the [C4.1 (Collective Code Construction Contract)](http://rfc.zeromq.org/spec:22) process for contributions.

CZMQ uses the [CLASS (C Language Style for Scalabilty)](http://rfc.zeromq.org/spec:21) guide for code style.

To report an issue, use the [CZMQ issue tracker](https://github.com/zeromq/czmq/issues) at github.com.

## Using CZMQ

### Install from a package manager

#### Linux

Deb packages are available for [Debian](https://packages.debian.org/search?searchon=sourcenames&keywords=czmq) and [Ubuntu](https://packages.ubuntu.com/search?searchon=sourcenames&keywords=czmq).

For other distros please refer to [pkgs.org](https://pkgs.org/download/czmq).

You can also get prebuild binaries for latest git `master` for most distros on openSUSE's Build Service:

**Git `master` only stable APIs:** http://software.opensuse.org/download.html?project=network%3Amessaging%3Azeromq%3Agit-stable&package=czmq

**Git `master` including draft APIs:** http://software.opensuse.org/download.html?project=network%3Amessaging%3Azeromq%3Agit-draft&package=czmq

#### MacOS

On macOS install czmq with Homebrew see [here](https://formulae.brew.sh/formula/czmq).

#### Windows

**Using vcpkg**

If you are already using [vcpkg](https://github.com/Microsoft/vcpkg/), you can download and install `czmq` with one single command:
```
vcpkg.exe install czmq
```
this will build `czmq` as a 32-bit shared library.
```
vcpkg.exe install czmq:x64-windows-static
```
this will build `czmq` as a 64-bit static library.

You may also build `czmq` with one or more optional libraries:
```
vcpkg.exe install czmq[curl,httpd,lz4]:x64-windows
```
this will build `czmq` with `libcurl`, `libmicrohttpd`, `lz4`, as a 64-bit shared library.

To use the draft APIs, you may build `czmq` with `draft` feature:
```
vcpkg install czmq[draft]
```

If you are an adventurer, and want to always use the lastest version of `czmq`, pass an extra `--head` option:
```
vcpkg.exe install czmq --head
```

These commands will also print out instructions on how to use the library from your MSBuild or CMake-based projects.

### Building on Linux and macOS

To start with, you need at least these packages:
* `git` -- git is how we share code with other people.
* `build-essential`, `libtool`, `pkg-config` - the C compiler and related tools.
* `autotools-dev`, `autoconf`, `automake` - the GNU autoconf makefile generators.
* `cmake` - the CMake makefile generators (an alternative to autoconf).

Plus some others:
* `uuid-dev`, `libpcre3-dev` - utility libraries.
* `valgrind` - a useful tool for checking your code.
* `pkg-config` - an optional useful tool to make building with dependencies easier.

Which we install like this (using the Debian-style apt-get package manager):

    sudo apt-get update
    sudo apt-get install -y \
        git build-essential libtool \
        pkg-config autotools-dev autoconf automake cmake \
        uuid-dev libpcre3-dev valgrind

    # only execute this next line if interested in updating the man pages as well (adds to build time):
    sudo apt-get install -y asciidoc

Here's how to build CZMQ from GitHub (building from packages is very similar, you don't clone a repo but unpack a tarball), including the libzmq (ZeroMQ core) library (NOTE: skip ldconfig on OSX):

    git clone https://github.com/zeromq/libzmq.git
    cd libzmq
    ./autogen.sh
    # do not specify "--with-libsodium" if you prefer to use internal tweetnacl security implementation (recommended for development)
    ./configure --with-libsodium
    make check
    sudo make install
    sudo ldconfig
    cd ..

    git clone https://github.com/zeromq/czmq.git
    cd czmq
    ./autogen.sh && ./configure && make check
    sudo make install
    sudo ldconfig
    cd ..

In general CZMQ works best with the latest libzmq master. If you already have an older version of libzmq installed on your system, e.g. in /usr/, then you can install libzmq master to your home directory ($HOME/local):

    #   Building libzmq in our home directory
    ./configure --prefix=$HOME/local

And then to build CZMQ against this installation of libzmq:

    export CFLAGS=-I$HOME/local/include
    export LDFLAGS=-L$HOME/local/lib64
    export PKG_CONFIG_PATH=$HOME/local/lib64/pkgconfig
    ./configure

NOTE: the PKG_CONFIG_PATH is not mandatory, and the actual directory might be different. If you cannot or do not want to use pkg-config, please make sure to MANUALLY add all the necessary CFLAGS and LDFLAGS from all dependencies (for example -DZMQ_BUILD_DRAFT_API=1 if you want the DRAFT APIs).

You will need the pkg-config, libtool, and autoreconf packages. After building, run the CZMQ selftests:

    make check

### Building on Windows

To start with, you need MS Visual Studio (C/C++). The free community edition works well.

Then, install git, and make sure it works from a DevStudio command prompt:

```
git
```

#### Using CMake

`czmq` requires `libzmq`, so we need to build `libzmq` first. For `libzmq`, you can optionally use [libsodium](https://github.com/jedisct1/libsodium) as the curve encryption library. So we will start from building `libsodium` in the following (and you can bypass the building of `libsodium` if you are ok with libzmq's default curve encryption library):
```
git clone --depth 1 -b stable https://github.com/jedisct1/libsodium.git
cd libsodium\builds\msvc\build
buildall.bat
cd ..\..\..\..
```
Once done, you can find the library files under `libsodium\bin\<Win32|x64>\<Debug|Release>\<Platform Toolset>\<dynamic|ltcg|static>`.

Here, the `<Platform Toolset>` is the platform toolset you are using: `v100` for `VS2010`, `v140` for `VS2015`, `v141` for `VS2017`, etc.

```
git clone https://github.com/zeromq/libzmq.git
cd libzmq
mkdir build
cd build
cmake .. -DBUILD_STATIC=OFF -DBUILD_SHARED=ON -DZMQ_BUILD_TESTS=ON -DWITH_LIBSODIUM=ON -DCMAKE_INCLUDE_PATH=..\libsodium\src\libsodium\include -DCMAKE_LIBRARY_PATH=..\libsodium\bin\Win32\Release\<Platform Toolset>\dynamic -DCMAKE_INSTALL_PREFIX=C:\libzmq
cmake --build . --config Release --target install
cd ..\..\
```
`-DWITH_LIBSODIUM=ON` is necessary if you want to build `libzmq` with `libsodium`. `CMAKE_INCLUDE_PATH` option tells `libzmq` where to search for `libsodium`'s header files. And the `CMAKE_LIBRARY_PATH` option tells where to search for libsodium library files. If you don't need `libsodium` support, you can omit these three options.

`-DCMAKE_INSTALL_PREFIX=C:\libzmq` means we want to install `libzmq` into the `C:\libzmq`. You may need to run your shell with administrator privilege in order to write to the system disk.

Now, it is time to build `czmq`:
```
git clone https://github.com/zeromq/czmq.git
cd czmq
mkdir build
cd build
cmake .. -DCZMQ_BUILD_SHARED=ON -DCZMQ_BUILD_STATIC=OFF -DCMAKE_PREFIX_PATH=C:\libzmq
cmake --build . --config Release
```
Remember that we install `libzmq` to `C:\libzmq` through specifying `-DCMAKE_INSTALL_PREFIX=C:\libzmq` in the previous step. We here use `-DCMAKE_PREFIX_PATH=C:\libzmq` to tell `czmq` where to search for `libzmq`.

That is not the whole story. We didn't mention the building of `libcurl`, `lz4`, `libuuid` and other `czmq` optional libraries above. In fact, to build all of these optional libraries successfully is really tricky. Please refer issue [#1972](https://github.com/zeromq/czmq/issues/1972) for more details.

#### Using MSBuild (Out of date, may not work now!)

```
    git clone --depth 1 -b stable https://github.com/jedisct1/libsodium.git
    cd libsodium\builds\msvc\build
    buildall.bat
    cd ..\..\..\..

    :: if libsodium is on disk, the Windows build of libzmq will automatically use it
    git clone https://github.com/zeromq/libzmq.git
    cd libzmq\builds\msvc
    configure.bat
    cd build
    buildall.bat
    cd ..\..\..\..

    git clone https://github.com/zeromq/czmq.git
    cd czmq\builds\msvc
    configure.bat
    cd build
    buildall.bat
    cd ..\..\..\..
```

Let's test by running `czmq_selftest`:

```
   czmq>dir/s/b czmq_selftest.exe
   czmq\builds\msvc\vs2013\DebugDEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\DebugLEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\DebugSEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\ReleaseDEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\ReleaseLEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\ReleaseSEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\DebugDEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\DebugLEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\DebugSEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\ReleaseDEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\ReleaseLEXE\czmq_selftest.exe
   czmq\builds\msvc\vs2013\x64\ReleaseSEXE\czmq_selftest.exe

    :: select your choice and run it
    czmq\builds\msvc\vs2013\x64\ReleaseDEXE\czmq_selftest.exe
```

### Linking with an Application

Include `czmq.h` in your application and link with libczmq. Here is a typical gcc link command:

    gcc myapp.c -o myapp -lczmq -lzmq

Note: if you want to use the draft APIs you'll need to define `CZMQ_BUILD_DRAFT_API=1` 
and `ZMQ_BUILD_DRAFT_API=1` in order to unlock them. This handled automatically 
by platforms using pkg-config but not through cmake on Windows for example.

### Use from Other Languages

This is a list of auto-generated bindings:

* https://github.com/zeromq/czmq/tree/master/bindings/jni - Java
* https://github.com/zeromq/czmq/tree/master/bindings/nodejs - NodeJS
* https://github.com/zeromq/czmq/tree/master/bindings/python - Python
* https://github.com/zeromq/czmq/tree/master/bindings/python_cffi - Python (cffi)
* https://github.com/zeromq/czmq/tree/master/bindings/qml - QML
* https://github.com/zeromq/czmq/tree/master/bindings/qt - Qt
* https://github.com/zeromq/czmq/tree/master/bindings/ruby - Ruby (FFI)

This is a list of known higher-level wrappers around CZMQ:

* https://github.com/1100110/CZMQ - D bindings
* https://github.com/methodmissing/rbczmq - Ruby
* https://github.com/paddor/cztop - Ruby, based on generated FFI binding
* https://github.com/zeromq/pyczmq - Python
* https://github.com/lhope/cl-czmq - Common Lisp
* https://github.com/fmp88/ocaml-czmq - Ocaml
* https://github.com/gar1t/erlang-czmq - Erlang
* https://github.com/mtortonesi/ruby-czmq-ffi - Ruby FFI
* https://github.com/zeromq/goczmq - Go

### API v3 Summary

This is the API provided by CZMQ v3.x, in alphabetical order.

.pull doc/zactor.doc
.pull doc/zauth.doc
.pull doc/zbeacon.doc
.pull doc/zcert.doc
.pull doc/zcertstore.doc
.pull doc/zchunk.doc
.pull doc/zclock.doc
.pull doc/zconfig.doc
.pull doc/zdigest.doc
.pull doc/zdir.doc
.pull doc/zdir_patch.doc
.pull doc/zfile.doc
.pull doc/zframe.doc
.pull doc/zgossip.doc
.pull doc/zhash.doc
.pull doc/zhashx.doc
.pull doc/ziflist.doc
.pull doc/zlist.doc
.pull doc/zlistx.doc
.pull doc/zloop.doc
.pull doc/zmonitor.doc
.pull doc/zmsg.doc
.pull doc/zpoller.doc
.pull doc/zproc.doc
.pull doc/zproxy.doc
.pull doc/zrex.doc
.pull doc/zsock.doc
.pull doc/zstr.doc
.pull doc/zsys.doc
.pull doc/ztimerset.doc
.pull doc/ztrie.doc
.pull doc/zuuid.doc

## Error Handling

The CZMQ policy is to reduce the error flow to 0/-1 where possible. libzmq still does a lot of errno setting. CZMQ does not do that, as it creates a fuzzy API. Things either work as expected, or they fail, and the application's best strategy is usually to assert on non-zero return codes.

Some older libraries still return plethora of error codes, to indicate different types of failure. This ironically makes both library and application more likely to be buggy. The reason is simply that it needs more code on both sides of the API, and the more code, the more bugs.

The use of black/white error handling fits the CLASS style for APIs where each call is explicit and without side effects of any kind, and where damage is either impossible, or fatal.

The one exception is running out of resources (memory, sockets). In that case, there are two strategies that work, for different types of app. One is to assert, to force better sizing of the machine and/or limits such as max connections. Two is to degrade carefully, e.g. refuse new connections, however that is considerably harder to do correctly and probably unrealistic for most developers.

Some CZMQ methods used to actually assert, e.g. in zsocket_bind, if the action failed, instead of returning -1. That was just closer to the majority case where the action MUST work, or nothing can continue. However there's a small slice of cases where failure means something positive, and for these cases, such calls return -1 on failure. 99% of calling code simply asserts the return value is not -1.

There are a few cases where the return value is overloaded to return -1, 0, or other values. These are somewhat confusing special cases and we aim to eliminate them over time.

The overall goal with this strategy is robustness, and absolute minimal and predictable expression in the code. You can see that it works: the CZMQ code is generally very simple and clear, with a few exceptions of places where people have used their old C style (we fix these over time).

## CZMQ Actors

The v2 API had a zthread class that let you create "attached threads" connected to their parent by an inproc:// PIPE socket. In v3 this has been simplified and better wrapped as the zactor class. CZMQ actors are in effect threads with a socket interface. A zactor_t instance works like a socket, and the CZMQ classes that deal with sockets (like zmsg and zpoller) all accept zactor_t references as well as zsock_t and libzmq void * socket handles.

To write an actor, use this template. Note that your actor is a single function "void myname (zsock_t *pipe, void *args)" function:

    /*  =========================================================================
        someclass - some description

        Copyright (c) the Contributors as noted in the AUTHORS file.
        This file is part of CZMQ, the high-level C binding for 0MQ:
        http://czmq.zeromq.org.

        This Source Code Form is subject to the terms of the Mozilla Public
        License, v. 2.0. If a copy of the MPL was not distributed with this
        file, You can obtain one at http://mozilla.org/MPL/2.0/.
        =========================================================================
    */

    /*
    @header
        Please take e.g. include/zmonitor.h as basis for your public API.
        And delete this text, and write your own, when you create an actor :-)
    @discuss

    @end
    */

    #include "../include/czmq.h"

    //  --------------------------------------------------------------------------
    //  The self_t structure holds the state for one actor instance

    typedef struct {
        zsock_t *pipe;              //  Actor command pipe
        zpoller_t *poller;          //  Socket poller
        //  ... you'll be adding other stuff here
        bool terminated;            //  Did caller ask us to quit?
        bool verbose;               //  Verbose logging enabled?
    } self_t;

    static self_t *
    s_self_new (zsock_t *pipe)
    {
        self_t *self = (self_t *) zmalloc (sizeof (self_t));
        self->pipe = pipe;
        //  ... initialize your own state including any other
        //  sockets, which you can add to the poller:
        self->poller = zpoller_new (self->pipe, NULL);
        return self;
    }

    static void
    s_self_destroy (self_t **self_p)
    {
        assert (self_p);
        if (*self_p) {
            self_t *self = *self_p;
            zpoller_destroy (&self->poller);
            //  ... destroy your own state here
            free (self);
            *self_p = NULL;
        }
    }


    //  --------------------------------------------------------------------------
    //  Handle a command from calling application

    static int
    s_self_handle_pipe (self_t *self)
    {
        //  Get the whole message off the pipe in one go
        zmsg_t *request = zmsg_recv (self->pipe);
        if (!request)
            return -1;                  //  Interrupted

        char *command = zmsg_popstr (request);
        if (self->verbose)
            zsys_info ("zxxx: API command=%s", command);
        if (streq (command, "VERBOSE"))
            self->verbose = true;
        else
        //  An example of a command that the caller would wait for
        //  via a signal, so that the two threads synchronize
        if (streq (command, "WAIT"))
            zsock_signal (self->pipe, 0);
        else
        if (streq (command, "$TERM"))
            self->terminated = true;
        else {
            zsys_error ("zxxx: - invalid command: %s", command);
            assert (false);
        }
        zstr_free (&command);
        zmsg_destroy (&request);
        return 0;
    }


    //  --------------------------------------------------------------------------
    //  zxxx() implements the zxxx actor interface

    void
    zxxx (zsock_t *pipe, void *args)
    {
        self_t *self = s_self_new (pipe);
        //  Signal successful initialization
        zsock_signal (pipe, 0);

        while (!self->terminated) {
            zsock_t *which = (zsock_t *) zpoller_wait (self->poller, -1);
            if (which == self->pipe)
                s_self_handle_pipe (self);
            else
            if (zpoller_terminated (self->poller))
                break;          //  Interrupted
        }
        s_self_destroy (&self);
    }


    //  --------------------------------------------------------------------------
    //  Selftest

    void
    zxxx_test (bool verbose)
    {
        printf (" * zxxx: ");
        if (verbose)
            printf ("\n");

        //  @selftest
        zactor_t *xxx = zactor_new (zxxx, NULL);
        assert (xxx);
        if (verbose)
            zstr_sendx (xxx, "VERBOSE", NULL);

        zactor_destroy (&xxx);
        //  @end
        printf ("OK\n");
    }

The selftest code shows how to create, talk to, and destroy an actor.

## Under the Hood

### Adding a New Class

If you define a new CZMQ class `myclass` you need to:

* Write the `zmyclass.c` and `zmyclass.h` source files, in `src` and `include` respectively.
* Add`#include <zmyclass.h>` to `include/czmq.h`.
* Add the myclass header and test call to `src/czmq_selftest.c`.
* Add a reference documentation to 'doc/zmyclass.txt'.
* Add myclass to 'model/projects.xml` and read model/README.txt.
* Add a section to README.txt.

### Documentation

Man pages are generated from the class header and source files via the doc/mkman tool, and similar functionality in the gitdown tool (http://github.com/imatix/gitdown). The header file for a class must wrap its interface as follows (example is from include/zclock.h):

    //  @interface
    //  Sleep for a number of milliseconds
    void
        zclock_sleep (int msecs);

    //  Return current system clock as milliseconds
    int64_t
        zclock_time (void);

    //  Self test of this class
    int
        zclock_test (Bool verbose);
    //  @end

The source file for a class must provide documentation as follows:

    /*
    @header
    ...short explanation of class...
    @discuss
    ...longer discussion of how it works...
    @end
    */

The source file for a class then provides the self test example as follows:

    //  @selftest
    int64_t start = zclock_time ();
    zclock_sleep (10);
    assert ((zclock_time () - start) >= 10);
    //  @end

The template for man pages is in doc/mkman.

### Development

CZMQ is developed through a test-driven process that guarantees no memory violations or leaks in the code:

* Modify a class or method.
* Update the test method for that class.
* Run the 'selftest' script, which uses the Valgrind memcheck tool.
* Repeat until perfect.

### Porting CZMQ

When you try CZMQ on an OS that it's not been used on (ever, or for a while), you will hit code that does not compile. In some cases the patches are trivial, in other cases (usually when porting to Windows), the work needed to build equivalent functionality may be non-trivial. In any case, the benefit is that once ported, the functionality is available to all applications.

Before attempting to patch code for portability, please read the `czmq_prelude.h` header file. There are several typical types of changes you may need to make to get functionality working on a specific operating system:

* Defining typedefs which are missing on that specific compiler: do this in czmq_prelude.h.
* Defining macros that rename exotic library functions to more conventional names: do this in czmq_prelude.h.
* Reimplementing specific methods to use a non-standard API: this is typically needed on Windows. Do this in the relevant class, using #ifdefs to properly differentiate code for different platforms.

### Hints to Contributors

CZMQ is a nice, neat library, and you may not immediately appreciate why. Read the CLASS style guide please, and write your code to make it indistinguishable from the rest of the code in the library. That is the only real criteria for good style: it's invisible.

Don't include system headers in source files. The right place for these is czmq_prelude.h. If you need to check against configured libraries and/or headers, include platform.h in the source before including czmq.h.

Do read your code after you write it and ask, "Can I make this simpler?" We do use a nice minimalist and yet readable style. Learn it, adopt it, use it.

Before opening a pull request read our [contribution guidelines](https://github.com/zeromq/czmq/blob/master/CONTRIBUTING.md). Thanks!

### Code Generation

We generate scripts for build systems like autotools, cmake and others as well as class skeletons, class headers, the selftest runner, bindings to higher level languages and more using zproject. Generated files will have a header and footer telling you that this file was generated. To re-generate those files it is recommended to use the latest `zeromqorg/zproject` docker image. 

#### Docker

* Clone [libzmq](https://github.com/zeromq/libzmq) into the same directory as czmq. 

Next always download the latest image: 

```sh
# Make sure 
docker pull zeromqorg/zproject:latest
```

Then run the following command:

```sh
# Shell and Powershell
docker run -v ${PWD}/..:/workspace -e BUILD_DIR=/workspace/czmq zeromqorg/zproject

# Windows CMD
docker run -v %cd%/..:/workspace -e BUILD_DIR=/workspace/czmq zeromqorg/zproject
```

#### Linux and MacOS

* Install [GSL](https://github.com/zeromq/gsl) and [zproject](https://github.com/zeromq/zproject)
* Clone [libzmq](https://github.com/zeromq/libzmq) into the same directory as czmq

Then run the following command:

	gsl project.xml

### This Document

