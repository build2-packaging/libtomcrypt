# libtomcrypt - Previously the git repository contained `doc/crypt

This is a `build2` package for the [`<UPSTREAM-NAME>`](https://<UPSTREAM-URL>)
C library. It provides <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using `libtomcrypt` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libtomcrypt ^<VERSION>
```

Then import the library in your `buildfile`:

```
import libs = libtomcrypt%lib{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
lib{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.libtomcrypt.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
