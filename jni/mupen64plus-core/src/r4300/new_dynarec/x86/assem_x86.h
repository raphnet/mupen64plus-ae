#ifndef M64P_R4300_ASSEM_X86_H
#define M64P_R4300_ASSEM_X86_H

#define HOST_REGS 8
#define HOST_CCREG 6
#define HOST_BTREG 5
#define EXCLUDE_REG 4

//#define IMM_PREFETCH 1
#define HOST_IMM_ADDR32 1
#define INVERTED_CARRY 1
#define DESTRUCTIVE_WRITEBACK 1
#define DESTRUCTIVE_SHIFT 1

#define USE_MINI_HT 1

#define TARGET_SIZE_2 25 // 2^25 = 32 megabytes
#define JUMP_TABLE_SIZE 0 // Not needed for 32-bit x86

/* x86 calling convention:
   caller-save: %eax %ecx %edx
   callee-save: %ebp %ebx %esi %edi */

void jump_vaddr_eax(void);
void jump_vaddr_ecx(void);
void jump_vaddr_edx(void);
void jump_vaddr_ebx(void);
void jump_vaddr_ebp(void);
void jump_vaddr_edi(void);
void invalidate_block_eax(void);
void invalidate_block_ecx(void);
void invalidate_block_edx(void);
void invalidate_block_ebx(void);
void invalidate_block_ebp(void);
void invalidate_block_esi(void);
void invalidate_block_edi(void);
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

extern u_int memory_map[1048576];
extern ALIGN(4, u_char restore_candidate[512]);

#endif /* M64P_R4300_ASSEM_X86_H */
