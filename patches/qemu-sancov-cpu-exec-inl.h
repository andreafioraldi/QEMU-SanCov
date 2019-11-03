#include "qemu-sancov-common.h"
#include <dlfcn.h>

__void_fn_void sancov_cb_trace_pc;

void *sancov_lib_handle;

void sancov_init(void)
{
    char *inst_lib = getenv("QEMU_SANCOV_LIB");
    if (!inst_lib) return;
    
    sancov_lib_handle = dlopen(inst_lib, RTLD_NOW | RTLD_LOCAL);
    if (!sancov_lib_handle) return;
    
    sancov_cb_trace_pc = (__void_fn_void)dlsym(sancov_lib_handle, SANCOV_TRACE_PC_NAME);
}


