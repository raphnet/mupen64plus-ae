/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - arm_profiler.h                                          *
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

#ifndef M64P_R4300_ARM_PROFILER_H
#define M64P_R4300_ARM_PROFILER_H

#ifdef NEW_DYNAREC_PROFILER
#ifndef PROFILER
void profiler_init(void);
void profiler_cleanup(void);
void profiler_block(int addr);
void set_tlb(void);
void copy_mapping(void * map);
#else

#include <capstone.h>
#define ARCHITECTURE CS_ARCH_ARM
#define MODE CS_MODE_LITTLE_ENDIAN
#define INSTRUCTION insn[i].detail->arm
#define FP_REGISTER 0x4d
#define CALL_INST 0xd

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

/* Abstract linkage_arm.S */
typedef struct
{
  char extra_memory[33554432];
  u_char dynarec_local[64];
  uint32_t next_interupt;
  int cycle_count;
  int last_count;
  int pending_exception;
  int pcaddr;
  int stop;
  char *invc_ptr;
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
  float *reg_cop1_simple[32];
  double *reg_cop1_double[32];
  u_int rounding_modes[4];
  int branch_target;
  uint32_t PC;
  precomp_instr fake_pc;
  int ram_offset;
  u_int mini_ht[32][2];
  u_char restore_candidate[512];
  u_int memory_map[1048576];
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

#define jump_vaddr_r0                      profiler_jump_vaddr_r0
#define jump_vaddr_r1                      profiler_jump_vaddr_r1
#define jump_vaddr_r2                      profiler_jump_vaddr_r2
#define jump_vaddr_r3                      profiler_jump_vaddr_r3
#define jump_vaddr_r4                      profiler_jump_vaddr_r4
#define jump_vaddr_r5                      profiler_jump_vaddr_r5
#define jump_vaddr_r6                      profiler_jump_vaddr_r6
#define jump_vaddr_r7                      profiler_jump_vaddr_r7
#define jump_vaddr_r8                      profiler_jump_vaddr_r8
#define jump_vaddr_r9                      profiler_jump_vaddr_r9
#define jump_vaddr_r10                     profiler_jump_vaddr_r10
#define jump_vaddr_r12                     profiler_jump_vaddr_r12
#define jump_vaddr                         profiler_jump_vaddr
#define invalidate_addr_r0                 profiler_invalidate_addr_r0
#define invalidate_addr_r1                 profiler_invalidate_addr_r1
#define invalidate_addr_r2                 profiler_invalidate_addr_r2
#define invalidate_addr_r3                 profiler_invalidate_addr_r3
#define invalidate_addr_r4                 profiler_invalidate_addr_r4
#define invalidate_addr_r5                 profiler_invalidate_addr_r5
#define invalidate_addr_r6                 profiler_invalidate_addr_r6
#define invalidate_addr_r7                 profiler_invalidate_addr_r7
#define invalidate_addr_r8                 profiler_invalidate_addr_r8
#define invalidate_addr_r9                 profiler_invalidate_addr_r9
#define invalidate_addr_r10                profiler_invalidate_addr_r10
#define invalidate_addr_r12                profiler_invalidate_addr_r12
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

static void jump_vaddr_r0(void){}
static void jump_vaddr_r1(void){}
static void jump_vaddr_r2(void){}
static void jump_vaddr_r3(void){}
static void jump_vaddr_r4(void){}
static void jump_vaddr_r5(void){}
static void jump_vaddr_r6(void){}
static void jump_vaddr_r7(void){}
static void jump_vaddr_r8(void){}
static void jump_vaddr_r9(void){}
static void jump_vaddr_r10(void){}
static void jump_vaddr_r12(void){}
static void jump_vaddr(void){}
static void invalidate_addr_r0(void){}
static void invalidate_addr_r1(void){}
static void invalidate_addr_r2(void){}
static void invalidate_addr_r3(void){}
static void invalidate_addr_r4(void){}
static void invalidate_addr_r5(void){}
static void invalidate_addr_r6(void){}
static void invalidate_addr_r7(void){}
static void invalidate_addr_r8(void){}
static void invalidate_addr_r9(void){}
static void invalidate_addr_r10(void){}
static void invalidate_addr_r12(void){}
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

/* Abstract arm_cpu_features.c */
static arm_cpu_features_t arm_cpu_features;
static void detect_arm_cpu_features(void){}
static void print_arm_cpu_features(void){}
#endif
#endif

#endif /* M64P_R4300_ARM_PROFILER_H */
