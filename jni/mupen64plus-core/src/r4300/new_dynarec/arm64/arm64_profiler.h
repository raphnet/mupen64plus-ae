/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - arm64_profiler.h                                        *
 *   Copyright (C) 2009-2011 Ari64                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef M64P_R4300_ARM64_PROFILER_H
#define M64P_R4300_ARM64_PROFILER_H

#ifdef NEW_DYNAREC_PROFILER
#ifndef PROFILER
void profiler_init(void);
void profiler_cleanup(void);
void profiler_block(int addr);
void set_tlb(void);
void copy_mapping(void * map);
#else

#include <capstone.h>
#define ARCHITECTURE CS_ARCH_ARM64
#define MODE CS_MODE_LITTLE_ENDIAN
#define INSTRUCTION insn[i].detail->arm64
#define FP_REGISTER 0x1
#define CALL_INST 0x15

#undef assert
#define assert(A)                                                                               \
  do{                                                                                           \
    if((A)==0) {                                                                                \
      __debugbreak();                                                                           \
    }                                                                                           \
  }                                                                                             \
  while(0)

/* Abstract non-static variables */
#define base_addr                          profiler_base_addr
#define out                                profiler_out
#define hash_table                         profiler_hash_table
#define jump_in                            profiler_jump_in
#define jump_dirty                         profiler_jump_dirty

/* Abstract non-static functions */
#define TLBWI_new                          profiler_TLBWI_new
#define TLBWR_new                          profiler_TLBWR_new
#define add_link                           profiler_add_link
#define clean_blocks                       profiler_clean_blocks
#define get_addr                           profiler_get_addr
#define get_addr_32                        profiler_get_addr_32
#define get_addr_ht                        profiler_get_addr_ht
#define invalidate_all_pages               profiler_invalidate_all_pages
#define invalidate_block                   profiler_invalidate_block
#define invalidate_cached_code_new_dynarec profiler_invalidate_cached_code_new_dynarec
#define new_dynarec_cleanup                profiler_new_dynarec_cleanup
#define new_dynarec_init                   profiler_new_dynarec_init
#define new_recompile_block                profiler_new_recompile_block

/* Abstract non read only external variables */
#define invalid_code                       profiler_invalid_code
static char invalid_code[0x100000];
/* TODO: Any others? */

/* Abstract linkage_arm64.S */
typedef struct
{
  char extra_memory[33554432];
  u_char dynarec_local[256];
  uint32_t next_interupt;
  int cycle_count;
  int last_count;
  int pending_exception;
  int pcaddr;
  int stop;
  uint64_t invc_ptr; //char *invc_ptr;
  uint32_t address;
  uint64_t readmem_dword;
  uint64_t cpu_dword;
  uint32_t cpu_word;
  uint16_t cpu_hword;
  uint8_t cpu_byte;
  uint32_t FCR0;
  uint32_t FCR31;
  int64_t reg[32];
  int64_t hi;
  int64_t lo;
  unsigned int g_cp0_regs[CP0_REGS_COUNT];
  uint64_t reg_cop1_simple[32]; //float *reg_cop1_simple[32];
  uint64_t reg_cop1_double[32]; //double *reg_cop1_double[32];
  u_int rounding_modes[4];
  int branch_target;
  uint64_t PC; //precomp_instr * PC;
  precomp_instr fake_pc;
  uint64_t ram_offset;
  uint64_t mini_ht[32][2];
  u_char restore_candidate[512];
  /*uint64_t*/u_int memory_map[1048576];
}profiler_t;

ALIGN(4096, static profiler_t profiler);

#define extra_memory                       profiler.extra_memory
#define dynarec_local                      profiler.dynarec_local
#define next_interupt                      profiler.next_interupt
#define cycle_count                        profiler.cycle_count
#define last_count                         profiler.last_count
#define pending_exception                  profiler.pending_exception
#define pcaddr                             profiler.pcaddr
#define stop                               profiler.stop
#define invc_ptr                           profiler.invc_ptr
#define address                            profiler.address
#define readmem_dword                      profiler.readmem_dword
#define cpu_dword                          profiler.cpu_dword
#define cpu_word                           profiler.cpu_word
#define cpu_hword                          profiler.cpu_hword
#define cpu_byte                           profiler.cpu_byte
#define FCR0                               profiler.FCR0
#define FCR31                              profiler.FCR31
#define reg                                profiler.reg
#define hi                                 profiler.hi
#define lo                                 profiler.lo
#define g_cp0_regs                         profiler.g_cp0_regs
#define reg_cop1_simple                    profiler.reg_cop1_simple
#define reg_cop1_double                    profiler.reg_cop1_double
#define rounding_modes                     profiler.rounding_modes
#define branch_target                      profiler.branch_target
#define PC                                 profiler.PC
#define fake_pc                            profiler.fake_pc
#define ram_offset                         profiler.ram_offset
#define mini_ht                            profiler.mini_ht
#define restore_candidate                  profiler.restore_candidate
#define memory_map                         profiler.memory_map
#define jump_vaddr_x0                      profiler_jump_vaddr_x0 
#define jump_vaddr_x1                      profiler_jump_vaddr_x1
#define jump_vaddr_x2                      profiler_jump_vaddr_x2
#define jump_vaddr_x3                      profiler_jump_vaddr_x3
#define jump_vaddr_x4                      profiler_jump_vaddr_x4
#define jump_vaddr_x5                      profiler_jump_vaddr_x5
#define jump_vaddr_x6                      profiler_jump_vaddr_x6
#define jump_vaddr_x7                      profiler_jump_vaddr_x7
#define jump_vaddr_x8                      profiler_jump_vaddr_x8
#define jump_vaddr_x9                      profiler_jump_vaddr_x9
#define jump_vaddr_x10                     profiler_jump_vaddr_x10
#define jump_vaddr_x11                     profiler_jump_vaddr_x11
#define jump_vaddr_x12                     profiler_jump_vaddr_x12
#define jump_vaddr_x13                     profiler_jump_vaddr_x13
#define jump_vaddr_x14                     profiler_jump_vaddr_x14
#define jump_vaddr_x15                     profiler_jump_vaddr_x15
#define jump_vaddr_x16                     profiler_jump_vaddr_x16
#define jump_vaddr_x17                     profiler_jump_vaddr_x17
#define jump_vaddr_x18                     profiler_jump_vaddr_x18
#define jump_vaddr_x19                     profiler_jump_vaddr_x19
#define jump_vaddr_x20                     profiler_jump_vaddr_x20
#define jump_vaddr_x21                     profiler_jump_vaddr_x21
#define jump_vaddr_x22                     profiler_jump_vaddr_x22
#define jump_vaddr_x23                     profiler_jump_vaddr_x23
#define jump_vaddr_x24                     profiler_jump_vaddr_x24
#define jump_vaddr_x25                     profiler_jump_vaddr_x25
#define jump_vaddr_x26                     profiler_jump_vaddr_x26
#define jump_vaddr_x27                     profiler_jump_vaddr_x27
#define jump_vaddr_x28                     profiler_jump_vaddr_x28
#define jump_vaddr                         profiler_jump_vaddr
#define invalidate_addr_x0                 profiler_invalidate_addr_x0
#define invalidate_addr_x1                 profiler_invalidate_addr_x1
#define invalidate_addr_x2                 profiler_invalidate_addr_x2
#define invalidate_addr_x3                 profiler_invalidate_addr_x3
#define invalidate_addr_x4                 profiler_invalidate_addr_x4
#define invalidate_addr_x5                 profiler_invalidate_addr_x5
#define invalidate_addr_x6                 profiler_invalidate_addr_x6
#define invalidate_addr_x7                 profiler_invalidate_addr_x7
#define invalidate_addr_x8                 profiler_invalidate_addr_x8
#define invalidate_addr_x9                 profiler_invalidate_addr_x9
#define invalidate_addr_x10                profiler_invalidate_addr_x10
#define invalidate_addr_x11                profiler_invalidate_addr_x11
#define invalidate_addr_x12                profiler_invalidate_addr_x12
#define invalidate_addr_x13                profiler_invalidate_addr_x13
#define invalidate_addr_x14                profiler_invalidate_addr_x14
#define invalidate_addr_x15                profiler_invalidate_addr_x15
#define invalidate_addr_x16                profiler_invalidate_addr_x16
#define invalidate_addr_x17                profiler_invalidate_addr_x17
#define invalidate_addr_x18                profiler_invalidate_addr_x18
#define invalidate_addr_x19                profiler_invalidate_addr_x19
#define invalidate_addr_x20                profiler_invalidate_addr_x20
#define invalidate_addr_x21                profiler_invalidate_addr_x21
#define invalidate_addr_x22                profiler_invalidate_addr_x22
#define invalidate_addr_x23                profiler_invalidate_addr_x23
#define invalidate_addr_x24                profiler_invalidate_addr_x24
#define invalidate_addr_x25                profiler_invalidate_addr_x25
#define invalidate_addr_x26                profiler_invalidate_addr_x26
#define invalidate_addr_x27                profiler_invalidate_addr_x27
#define invalidate_addr_x28                profiler_invalidate_addr_x28
#define indirect_jump_indexed              profiler_indirect_jump_indexed
#define indirect_jump                      profiler_indirect_jump
#define verify_code                        profiler_verify_code
#define verify_code_vm                     profiler_verify_code_vm
#define verify_code_ds                     profiler_verify_code_ds
#define cc_interrupt                       profiler_cc_interrupt
#define do_interrupt                       profiler_do_interrupt
#define fp_exception                       profiler_fp_exception
#define fp_exception_ds                    profiler_fp_exception_ds
#define jump_syscall                       profiler_jump_syscall
#define jump_eret                          profiler_jump_eret
#define read_nomem_new                     profiler_read_nomem_new
#define read_nomemb_new                    profiler_read_nomemb_new
#define read_nomemh_new                    profiler_read_nomemh_new
#define read_nomemd_new                    profiler_read_nomemd_new
#define write_nomem_new                    profiler_write_nomem_new
#define write_nomemb_new                   profiler_write_nomemb_new
#define write_nomemh_new                   profiler_write_nomemh_new
#define write_nomemd_new                   profiler_write_nomemd_new
#define write_rdram_new                    profiler_write_rdram_new
#define write_rdramb_new                   profiler_write_rdramb_new
#define write_rdramh_new                   profiler_write_rdramh_new
#define write_rdramd_new                   profiler_write_rdramd_new
#define __clear_cache                      profiler_clear_cache

static void jump_vaddr_x0(void){}
static void jump_vaddr_x1(void){}
static void jump_vaddr_x2(void){}
static void jump_vaddr_x3(void){}
static void jump_vaddr_x4(void){}
static void jump_vaddr_x5(void){}
static void jump_vaddr_x6(void){}
static void jump_vaddr_x7(void){}
static void jump_vaddr_x8(void){}
static void jump_vaddr_x9(void){}
static void jump_vaddr_x10(void){}
static void jump_vaddr_x11(void){}
static void jump_vaddr_x12(void){}
static void jump_vaddr_x13(void){}
static void jump_vaddr_x14(void){}
static void jump_vaddr_x15(void){}
static void jump_vaddr_x16(void){}
static void jump_vaddr_x17(void){}
static void jump_vaddr_x18(void){}
static void jump_vaddr_x19(void){}
static void jump_vaddr_x20(void){}
static void jump_vaddr_x21(void){}
static void jump_vaddr_x22(void){}
static void jump_vaddr_x23(void){}
static void jump_vaddr_x24(void){}
static void jump_vaddr_x25(void){}
static void jump_vaddr_x26(void){}
static void jump_vaddr_x27(void){}
static void jump_vaddr_x28(void){}
static void jump_vaddr(void){}
static void invalidate_addr_x0(void){}
static void invalidate_addr_x1(void){}
static void invalidate_addr_x2(void){}
static void invalidate_addr_x3(void){}
static void invalidate_addr_x4(void){}
static void invalidate_addr_x5(void){}
static void invalidate_addr_x6(void){}
static void invalidate_addr_x7(void){}
static void invalidate_addr_x8(void){}
static void invalidate_addr_x9(void){}
static void invalidate_addr_x10(void){}
static void invalidate_addr_x11(void){}
static void invalidate_addr_x12(void){}
static void invalidate_addr_x13(void){}
static void invalidate_addr_x14(void){}
static void invalidate_addr_x15(void){}
static void invalidate_addr_x16(void){}
static void invalidate_addr_x17(void){}
static void invalidate_addr_x18(void){}
static void invalidate_addr_x19(void){}
static void invalidate_addr_x20(void){}
static void invalidate_addr_x21(void){}
static void invalidate_addr_x22(void){}
static void invalidate_addr_x23(void){}
static void invalidate_addr_x24(void){}
static void invalidate_addr_x25(void){}
static void invalidate_addr_x26(void){}
static void invalidate_addr_x27(void){}
static void invalidate_addr_x28(void){}
static void indirect_jump_indexed(void){}
static void indirect_jump(void){}
static void verify_code(void){}
static void verify_code_vm(void){}
static void verify_code_ds(void){}
static void cc_interrupt(void){}
static void do_interrupt(void){}
static void fp_exception(void){}
static void fp_exception_ds(void){}
static void jump_syscall(void){}
static void jump_eret(void){}
static void read_nomem_new(void){}
static void read_nomemb_new(void){}
static void read_nomemh_new(void){}
static void read_nomemd_new(void){}
static void write_nomem_new(void){}
static void write_nomemb_new(void){}
static void write_nomemh_new(void){}
static void write_nomemd_new(void){}
static void write_rdram_new(void){}
static void write_rdramb_new(void){}
static void write_rdramh_new(void){}
static void write_rdramd_new(void){}
static void __clear_cache(char* begin, char *end){}
#endif
#endif

#endif /* M64P_R4300_ARM64_PROFILER_H */
