#ifndef __QEMU_SANCOV_H__
#define __QEMU_SANCOV_H__

#define SANCOV_TRACE_PC_NAME "__sanitizer_cov_trace_pc"

typedef void (*__void_fn_void)(void);

extern __void_fn_void sancov_cb_trace_pc;

extern abi_ulong sancov_entry_point;
extern abi_ulong sancov_code_start;
extern abi_ulong sancov_code_end;

void sancov_init(void);

void sancov_gen_void_fn_ulong_call(void* fn, target_ulong arg0);

#endif
