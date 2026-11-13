# libtomcrypt - Cryptographic toolkit C library

This is a `build2` package repository for
[`libtomcrypt`](https://github.com/libtom/libtomcrypt), a modular and portable
cryptographic toolkit written in C.

This file contains setup instructions and other details for developing the
package. If you want to use `libtomcrypt` in your `build2`-based project, then
see the accompanying
[`PACKAGE-README.md`](libtomcrypt/PACKAGE-README.md) file instead.

The development setup for `libtomcrypt` uses the standard `bdep`-based
workflow. For example:

```
git clone --recurse-submodules .../libtomcrypt.git
cd libtomcrypt

bdep init -C @gcc cc config.c=gcc
bdep update
bdep test
```

The package patches one upstream source file. See
[`libtomcrypt/README-DEV`](libtomcrypt/README-DEV) for details.
