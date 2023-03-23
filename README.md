# grln - Group lines together

group line, or `grln` for short, group lines that belong together, normally;
by the colorizing them with the same color.

[![demo](https://asciinema.org/a/KMSFkQjC3Ep5W3SnIb9Bj7rtM.svg)](https://asciinema.org/a/KMSFkQjC3Ep5W3SnIb9Bj7rtM?autoplay=1)

## Hacking

Use `make` to compile, build and install `grln`. 

1. Compile the source code:

```sh
make
```

2. Optionally, execute our test-suite:

```sh
make test
```

The test suite relies on shell-script, `/bin/bash`, and a few standards
unix tools (i.e: `sed`, `grep`, etc.).

3. Finally, install it:

```sh
sudo make install
```

The `grln` binary should be available at `/usr/local/bin/grln` and, as long as this directory
is configured in your `$PATH` library, you can run `grln`.
