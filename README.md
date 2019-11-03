# QEMU-SanCov

Very WIP project. SanCov hooks and coverage reports for QEMU user.

Create a shared library with the user-defined hooks and load it in QEMU-SanCov
using the QEMU_SANCOV_LIB env var.

At the moment only the equivalent to `-fsanitize-coverage=bb,no-prune,trace-pc` is supported.

### Build

```sh
$./build_qemu.sh
```

### Examples

```sh
$ gcc -fPIC -shared examples/bbs_dump.c -o bbs_dump.so
$ QEMU_SANCOV_LIB=./bbs_dump.so ./qemu-sancov-x86_64 /bin/ls
```
