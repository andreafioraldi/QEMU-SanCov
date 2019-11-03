#include "qemu-sancov-common.h"
#include <dlfcn.h>

t_void_fn_void sancov_cb_trace_pc;
t_void_fn_u8_u8 sancov_cb_trace_cmp1;
t_void_fn_u16_u16 sancov_cb_trace_cmp2;
t_void_fn_u32_u32 sancov_cb_trace_cmp4;
t_void_fn_u64_u64 sancov_cb_trace_cmp8;

void *sancov_lib_handle;

void sancov_init(void)
{
    char *inst_lib = getenv("QEMU_SANCOV_LIB");
    if (!inst_lib) return;
    
    sancov_lib_handle = dlopen(inst_lib, RTLD_NOW | RTLD_LOCAL);
    if (!sancov_lib_handle) return;
    
    sancov_cb_trace_pc = (t_void_fn_void)dlsym(sancov_lib_handle, SANCOV_TRACE_PC_NAME);
    sancov_cb_trace_cmp1 = (t_void_fn_u8_u8)dlsym(sancov_lib_handle, SANCOV_TRACE_CMP1_NAME);
    sancov_cb_trace_cmp2 = (t_void_fn_u16_u16)dlsym(sancov_lib_handle, SANCOV_TRACE_CMP2_NAME);
    sancov_cb_trace_cmp4 = (t_void_fn_u32_u32)dlsym(sancov_lib_handle, SANCOV_TRACE_CMP4_NAME);
    sancov_cb_trace_cmp8 = (t_void_fn_u64_u64)dlsym(sancov_lib_handle, SANCOV_TRACE_CMP8_NAME);
}


