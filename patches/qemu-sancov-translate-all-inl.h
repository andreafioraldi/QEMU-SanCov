#include "qemu-sancov-common.h"

void sancov_gen_trace_pc(target_ulong pc)
{
    if (!sancov_cb_trace_pc || pc < sancov_code_start || pc > sancov_code_end)
        return;
    
    sancov_gen_void_fn_ulong_call((void*)sancov_cb_trace_pc, pc);
}
