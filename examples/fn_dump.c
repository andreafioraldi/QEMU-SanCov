#include <stdio.h>
#include <stdint.h>

void __cyg_profile_func_enter(void* func, void* caller) {
    fprintf(stderr, " %p: call %p\n", caller, func);
}

void __cyg_profile_func_exit(void* func, void* caller) {
    // here, atm, func is the address of the ret and not the function address like in SanCov
    fprintf(stderr, " %p: ret %p\n", func, caller);
}

