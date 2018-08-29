Copyright (c) 2009-2013 Toscoin Developers
Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.


See readme-qt.rst for instructions on building TosCoin-Qt, the
graphical user interface.

WINDOWS BUILD NOTES
===================

Compilers Supported
-------------------
TODO: What works?
Note: releases are cross-compiled using mingw running on Linux.


Dependencies
------------
Libraries you need to download separately and build:

                default path               download
OpenSSL         \openssl-1.0.2d-mgw        http://www.openssl.org/source/
Berkeley DB     \db-4.8.30.NC-mgw          http://download.oracle.com/
Boost           \boost-1.53.0-mgw          http://www.boost.org/
miniupnpc       \miniupnpc-1.9-mgw         http://miniupnp.free.fr/

Their licenses:

	OpenSSL        Old BSD license with the problematic advertising requirement
	Berkeley DB    New BSD license with additional requirement that linked software must be free open source
	Boost          MIT-like license
	miniupnpc      New (3-clause) BSD license

Versions used in this release:

	OpenSSL      1.0.2d
	Berkeley DB  4.8.30.NC
	Boost        1.53.0
	miniupnpc    1.9


OpenSSL
-------
MSYS shell:

un-tar sources with MSYS 'tar xfz' to avoid issue with symlinks (OpenSSL ticket 2377)
change 'MAKE' env. variable from 'C:\MinGW32\bin\mingw32-make.exe' to '/c/MinGW32/bin/mingw32-make.exe'

	cd /c/openssl-1.0.2d-mgw
	./Configure no-zlib no-shared no-dso no-krb5 no-camellia no-capieng no-cast no-cms no-dtls1 no-gost no-gmp no-heartbeats no-idea no-jpake no-md2 no-mdc2 no-rc5 no-rdrand no-rfc3779 no-rsax no-sctp no-seed no-sha0 no-static_engine no-whirlpool no-rc2 no-rc4 no-ssl2 no-ssl3 mingw
	make depend
	make

Issue:

In file included from dh_kdf.c:58:0:
../../include/openssl/cms.h:61:4: error: #error CMS is disabled. (https://stackoverflow.com/questions/44933463/openssl-with-no-cms-options-complains-no-cms-with-make-depend)

modify in crypto/dh/dh.kdf.c

	#include <openssl/dh.h>
    #include <openssl/evp.h>
    #include <openssl/asn1.h>
    - #include <openssl/cms.h>
    + #include <openssl/x509.h>
    +
    + #ifndef OPENSSL_NO_CMS
    + # include <openssl/cms.h>
    + #endif

Berkeley DB
-----------
MSYS shell:

	cd /c/db-4.8.30.NC-mgw/build_unix
	../dist/configure --enable-mingw --enable-cxx --disable-shared --disable-replication
	make

Issue:

make: *** [mut_failchk.o] Error 1 (https://bitcointalk.org/index.php?topic=45507.0)

modify in bulid_unix/db.h:

	typedef pthread_t db_threadid_t;	
   to
	typedef u_int32_t db_threadid_t;

Boost
-----
DOS prompt:

	cd \boost-1.53.0-mgw
	.\bootstrap.bat
	.\bootstrap.bat mingw
	.\b2.exe install toolset=gcc --prefix=boost-1.53.0-mgw\b2_for_mingw
	set PATH=%PATH%;boost-1.53.0-mgw\b2_for_mingw\bin
	b2 toolset=gcc --build-type=complete stage --with-chrono --with-filesystem --with-program_options --with-system --with-thread

MiniUPnPc
---------
UPnP support is optional, make with `USE_UPNP=` to disable it.

MSYS shell:

	cd /c/miniupnpc-1.9-mgw
	mingw32-make -f Makefile.mingw init upnpc-static

Issue:

c:/mingw/bin/../lib/gcc/mingw32/4.7.2/../../../../mingw32/bin/ld.exe: warning: cannot find entry symbol nable-stdcall-fixup; defaulting to 00401000 
(https://miniupnp.tuxfamily.org/forum/viewtopic.php?p=3654)

modify in Makefile.mingw

    upnpc-static:    upnpc.o libminiupnpc.a
    	$(CC) -Wl,-enable-stdcall-fixup -o $@ $^ $(LDLIBS)

    upnpc-shared:    dll/upnpc.o miniupnpc.lib
    	$(CC) -Wl,-enable-stdcall-fixup -o $@ $^ $(LDLIBS)

TosCoin
-------
DOS prompt:

	cd \TosCoin
	qmake "USE_UPNP=1" coin-qt.pro
	mingw32-make -f Makefile.Release

T.osCoin in release directory

TosCoin - Debug
-------
DOS prompt:

	cd \TosCoin
	qmake "USE_UPNP=1" coin-qt.pro
	mingw32-make -f Makefile.Debug

T.osCoin-debug in debug directory