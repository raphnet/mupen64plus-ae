#ifndef M64P_R4300_ASSEM_ARM_H
#define M64P_R4300_ASSEM_ARM_H

#define HOST_REGS 13
#define HOST_CCREG 10
#define HOST_BTREG 8
#define EXCLUDE_REG 11

#define HOST_IMM8 1
#define HAVE_CMOV_IMM 1
#define CORTEX_A8_BRANCH_PREDICTION_HACK 1
#define USE_MINI_HT 1
//#define REG_PREFETCH 1
#define HAVE_CONDITIONAL_CALL 1
#define RAM_OFFSET 1

/* ARM calling convention:
   r0-r3, r12: caller-save
   r4-r11: callee-save */

#define ARG1_REG 0
#define ARG2_REG 1
#define ARG3_REG 2
#define ARG4_REG 3

/* GCC register naming convention:
   r10 = sl (base)
   r11 = fp (frame pointer)
   r12 = ip (scratch)
   r13 = sp (stack pointer)
   r14 = lr (link register)
   r15 = pc (program counter) */

#define FP 11
#define LR 14
#define HOST_TEMPREG 14

// Note: FP is set to &dynarec_local when executing generated code.
// Thus the local variables are actually global and not on the stack.

#define BASE_ADDR ((int)(&extra_memory))
#define TARGET_SIZE_2 25 // 2^25 = 32 megabytes
#define JUMP_TABLE_SIZE (sizeof(jump_table_symbols)*2)

void jump_vaddr(void);
void jump_vaddr_r0(void);
void jump_vaddr_r1(void);
void jump_vaddr_r2(void);
void jump_vaddr_r3(void);
void jump_vaddr_r4(void);
void jump_vaddr_r5(void);
void jump_vaddr_r6(void);
void jump_vaddr_r7(void);
void jump_vaddr_r8(void);
void jump_vaddr_r9(void);
void jump_vaddr_r10(void);
void jump_vaddr_r12(void);
void invalidate_addr_r0(void);
void invalidate_addr_r1(void);
void invalidate_addr_r2(void);
void invalidate_addr_r3(void);
void invalidate_addr_r4(void);
void invalidate_addr_r5(void);
void invalidate_addr_r6(void);
void invalidate_addr_r7(void);
void invalidate_addr_r8(void);
void invalidate_addr_r9(void);
void invalidate_addr_r10(void);
void invalidate_addr_r12(void);
void indirect_jump_indexed(void);
void indirect_jump(void);
void verify_code(void);
void verify_code_vm(void);
void verify_code_ds(void);
void cc_interrupt(void);
void do_interrupt(void);
void fp_exception(void);
void fp_exception_ds(void);
void jump_syscall(void);
void jump_eret(void);
void read_nomem_new(void);
void read_nomemb_new(void);
void read_nomemh_new(void);
void read_nomemd_new(void);
void write_nomem_new(void);
void write_nomemb_new(void);
void write_nomemh_new(void);
void write_nomemd_new(void);
void write_rdram_new(void);
void write_rdramb_new(void);
void write_rdramh_new(void);
void write_rdramd_new(void);

/* bug-fix to implement __clear_cache (missing in Android; http://code.google.com/p/android/issues/detail?id=1803) */
void __clear_cache_bugfix(char* begin, char *end);
#ifdef ANDROID
  #define __clear_cache __clear_cache_bugfix
#endif

extern char *invc_ptr;
extern char extra_memory[33554432];
extern int cycle_count;
extern int last_count;
extern int branch_target;
extern int ram_offset;
extern uint64_t readmem_dword;
extern precomp_instr fake_pc;
extern void *dynarec_local;
extern u_int memory_map[1048576];
extern u_int mini_ht[32][2];
extern u_int rounding_modes[4];
extern u_char restore_candidate[512];

#endif /* M64P_R4300_ASSEM_ARM_H */
