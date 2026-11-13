# libtomcrypt - Cryptographic toolkit C library

This is a `build2` package for the
[`libtomcrypt`](https://github.com/libtom/libtomcrypt) C library. It provides
a modular and portable cryptographic toolkit that implements a wide range of
well-known published algorithms, from block ciphers and hash functions to
public key cryptography.


## Usage

To start using `libtomcrypt` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libtomcrypt ^1.18.2
```

Then import the library in your `buildfile`:

```
import libs = libtomcrypt%lib{tomcrypt}
```

The library interface is declared in the `<tomcrypt.h>` header.

The library is built with the default upstream configuration (see
`<tomcrypt_custom.h>`), which enables all the algorithms. Note that this
configuration doesn't define `LTC_PTHREAD`, so the library doesn't protect
its descriptor tables and PRNG states with mutexes.

Public key algorithms use [`libtommath`](https://cppget.org/libtommath) as
their math library, which the application selects before calling them:

```
ltc_mp = ltm_desc;
```

Note that with MSVC only the static library is built since `<tomcrypt.h>`
declares global data that is part of the interface (such as `ltc_mp`)
without `__declspec(dllimport)`, which MSVC requires to access data in a
DLL.
