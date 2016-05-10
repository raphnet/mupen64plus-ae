/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - x86_profiler.h                                          *
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

#ifndef M64P_R4300_X86_PROFILER_H
#define M64P_R4300_X86_PROFILER_H

#ifdef NEW_DYNAREC_PROFILER
#ifndef PROFILER
void profiler_init(void);
void profiler_cleanup(void);
void profiler_block(int addr);
void set_tlb(void);
void copy_mapping(void * map);
#else

#include <capstone.h>
#define ARCHITECTURE CS_ARCH_X86
#define MODE CS_MODE_32
#define INSTRUCTION insn[i].detail->x86
#define CALL_INST 0x38

/* Abstract non-static variables */
#define base_addr                          profiler_base_addr
#define out                                profiler_out
#define hash_table                         profiler_hash_table
#define jump_in                            profiler_jump_in
#define jump_dirty                         profiler_jump_dirty
#define cycle_count                        profiler_cycle_count
#define last_count                         profiler_last_count
#define pcaddr                             profiler_pcaddr
#define pending_exception                  profiler_pending_exception
#define branch_target                      profiler_branch_target
#define readmem_dword                      profiler_readmem_dword
#define memory_map                         profiler_memory_map
#define restore_candidate                  profiler_restore_candidate

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

ALIGN(16, static char extra_memory[33554432]);

extern u_int memory_map[1048576];
extern ALIGN(4, u_char restore_candidate[512]);
#endif
#endif

#endif /* M64P_R4300_X86_PROFILER_H */
