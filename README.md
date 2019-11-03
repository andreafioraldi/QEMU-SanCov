# QEMU-SanCov

Very WIP project. SanCov hooks and coverage reports for QEMU user.

Create a shared library with the user-defined hooks and load it in QEMU-SanCov
using the QEMU_SANCOV_LIB env var.

At the moment only the equivalent to `-fsanitize-coverage=bb,no-prune,trace-pc,trace-cmp -finstrument-functions` is supported.

> trace-cmp only in x86/x86_64

### Build

```sh
$./build_qemu.sh
```

### Examples

```sh
$ gcc test-instr.c -o test-instr
```

```sh
$ gcc -fPIC -shared examples/bbs_dump.c -o bbs_dump.so
$ QEMU_SANCOV_LIB=./bbs_dump.so ./qemu-sancov-x86_64 ./test-instr 0
```

```sh
$ gcc -fPIC -shared examples/cmp_dump.c -o cmp_dump.so
$ QEMU_SANCOV_LIB=./cmp_dump.so ./qemu-sancov-x86_64 ./test-instr 0
```

```sh
$ gcc -fPIC -shared examples/fn_dump.c -o fn_dump.so
$ QEMU_SANCOV_LIB=./fn_dump.so ./qemu-sancov-x86_64 ./test-instr 0
```
