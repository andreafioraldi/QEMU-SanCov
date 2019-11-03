#ifndef __QEMU_SANCOV_H__
#define __QEMU_SANCOV_H__

#include <stdint.h>

#define SANCOV_TRACE_PC_NAME "__sanitizer_cov_trace_pc"
#define SANCOV_TRACE_CMP1_NAME "__sanitizer_cov_trace_cmp1"
#define SANCOV_TRACE_CMP2_NAME "__sanitizer_cov_trace_cmp2"
#define SANCOV_TRACE_CMP4_NAME "__sanitizer_cov_trace_cmp4"
#define SANCOV_TRACE_CMP8_NAME "__sanitizer_cov_trace_cmp8"
#define SANCOV_TRACE_FN_ENTER_NAME "__cyg_profile_func_enter"
#define SANCOV_TRACE_FN_EXIT_NAME "__cyg_profile_func_exit"

typedef void (*t_void_fn_void)(void);
typedef void (*t_void_fn_u8_u8)(uint8_t, uint8_t);
typedef void (*t_void_fn_u16_u16)(uint8_t, uint8_t);
typedef void (*t_void_fn_u32_u32)(uint8_t, uint8_t);
typedef void (*t_void_fn_u64_u64)(uint8_t, uint8_t);
typedef void (*t_void_fn_ptr_ptr)(void*, void*);

extern t_void_fn_void sancov_cb_trace_pc;
extern t_void_fn_u8_u8 sancov_cb_trace_cmp1;
extern t_void_fn_u16_u16 sancov_cb_trace_cmp2;
extern t_void_fn_u32_u32 sancov_cb_trace_cmp4;
extern t_void_fn_u64_u64 sancov_cb_trace_cmp8;
extern t_void_fn_ptr_ptr sancov_cb_profile_func_enter;
extern t_void_fn_ptr_ptr sancov_cb_profile_func_exit;

extern abi_ulong sancov_entry_point;
extern abi_ulong sancov_code_start;
extern abi_ulong sancov_code_end;

void sancov_init(void);

void sancov_gen_void_fn_ulong_call(void* fn, target_ulong arg0);
void sancov_gen_void_fn_TCGv_TCGv_call(void* fn, TCGv_i64 arg0, TCGv_i64 arg1);
void sancov_gen_void_fn_TCGv_ulong_call(void* fn, TCGv_i64 arg0, target_ulong arg1);
void sancov_gen_void_fn_ulong_TCGv_call(void* fn, target_ulong arg0, TCGv_i64 arg1);
void sancov_gen_void_fn_ulong_ulong_call(void* fn, target_ulong arg0, target_ulong arg1);

#endif
