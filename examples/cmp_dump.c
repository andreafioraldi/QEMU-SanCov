#include <stdio.h>
#include <stdint.h>

void __sanitizer_cov_trace_cmp1(uint8_t a0, uint8_t a1) {
    fprintf(stderr, "[ Cmp 1 ] %p < %x, %x >\n", __builtin_return_address(0), a0, a1);
}

void __sanitizer_cov_trace_cmp2(uint16_t a0, uint16_t a1) {
    fprintf(stderr, "[ Cmp 2 ] %p < %x, %x >\n", __builtin_return_address(0), a0, a1);
}

void __sanitizer_cov_trace_cmp4(uint32_t a0, uint32_t a1) {
    fprintf(stderr, "[ Cmp 4 ] %p < %x, %x >\n", __builtin_return_address(0), a0, a1);
}

void __sanitizer_cov_trace_cmp8(uint64_t a0, uint64_t a1) {
    fprintf(stderr, "[ Cmp 8 ] %p < %lx, %lx >\n", __builtin_return_address(0), a0, a1);
}
