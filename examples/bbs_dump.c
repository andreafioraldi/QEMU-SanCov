#include <stdio.h>

void __sanitizer_cov_trace_pc(void) {
    fprintf(stderr, "[ BBs Dump ] %p\n", __builtin_return_address(0));
}
