/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - profiler.c                                              *
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

#ifdef NEW_DYNAREC_PROFILER
#undef NEW_DYNAREC
#define NEW_DYNAREC NEW_DYNAREC_PROFILER
#define PROFILER

#include "new_dynarec_64.c"

//#define DISASM_BLOCK
static int disasm_block[]={0xa400000};

typedef struct{
  intptr_t addr;
  int32_t size;
  char * name;
}Variable_t;

static const Variable_t var[] = {
#if NEW_DYNAREC_PROFILER >= NEW_DYNAREC_ARM
  {(intptr_t)&dynarec_local, sizeof(dynarec_local), "dynarec_local"},
  {(intptr_t)&invc_ptr, sizeof(invc_ptr), "invc_ptr"},
  {(intptr_t)&ram_offset, sizeof(ram_offset), "ram_offset"},
#endif
  {(intptr_t)&next_interupt, sizeof(next_interupt), "next_interupt"},
  {(intptr_t)&cycle_count, sizeof(cycle_count), "cycle_count"},
  {(intptr_t)&last_count, sizeof(last_count), "last_count"},
  {(intptr_t)&pending_exception, sizeof(pending_exception), "pending_exception"},
  {(intptr_t)&pcaddr, sizeof(pcaddr), "pcaddr"},
  {(intptr_t)&stop, sizeof(stop), "stop"},
  {(intptr_t)&address, sizeof(address), "address"},
  {(intptr_t)&readmem_dword, sizeof(readmem_dword), "readmem_dword"},
  {(intptr_t)&cpu_dword, sizeof(cpu_dword), "cpu_dword"},
  {(intptr_t)&cpu_word, sizeof(cpu_word), "cpu_word"},
  {(intptr_t)&cpu_hword, sizeof(cpu_hword), "cpu_hword"},
  {(intptr_t)&cpu_byte, sizeof(cpu_byte), "cpu_byte"},
  {(intptr_t)&FCR0, sizeof(FCR0), "FCR0"},
  {(intptr_t)&FCR31, sizeof(FCR31), "FCR31"},
  {(intptr_t)&reg, sizeof(reg), "reg"},
  {(intptr_t)&hi, sizeof(hi), "hi"},
  {(intptr_t)&lo, sizeof(lo), "lo"},
  {(intptr_t)&g_cp0_regs, sizeof(g_cp0_regs), "g_cp0_regs"},
  {(intptr_t)&reg_cop1_simple, sizeof(reg_cop1_simple), "reg_cop1_simple"},
  {(intptr_t)&reg_cop1_double, sizeof(reg_cop1_double), "reg_cop1_double"},
  {(intptr_t)&rounding_modes, sizeof(rounding_modes), "rounding_modes"},
  {(intptr_t)&branch_target, sizeof(branch_target), "branch_target"},
  {(intptr_t)&PC, sizeof(PC), "PC"},
  {(intptr_t)&fake_pc, sizeof(fake_pc), "fake_pc"},
  {(intptr_t)&mini_ht, sizeof(mini_ht), "mini_ht"},
  {(intptr_t)&restore_candidate, sizeof(restore_candidate), "restore_candidate"},
  {(intptr_t)&memory_map, sizeof(memory_map), "memory_map"},
  {-1, -1, NULL},
};

typedef struct{
  intptr_t addr;
  char * name;
}Function_t;

static Function_t func[] = {
  {(intptr_t)NULL /*MFC0*/, "MFC0"},
  {(intptr_t)NULL /*MTC0*/, "MTC0"},
  {(intptr_t)NULL /*TLBR*/, "TLBR"},
  {(intptr_t)NULL /*TLBP*/, "TLBP"},
#if NEW_DYNAREC_PROFILER >= NEW_DYNAREC_ARM
  {(intptr_t)invalidate_addr, "invalidate_addr"},
  {(intptr_t)jump_vaddr, "jump_vaddr"},
  {(intptr_t)indirect_jump_indexed, "indirect_jump_indexed"},
  {(intptr_t)indirect_jump, "indirect_jump"},
#if NEW_DYNAREC_PROFILER == NEW_DYNAREC_ARM64
  {(intptr_t)jump_vaddr_x0, "jump_vaddr_x0"},
  {(intptr_t)jump_vaddr_x1, "jump_vaddr_x1"},
  {(intptr_t)jump_vaddr_x2, "jump_vaddr_x2"},
  {(intptr_t)jump_vaddr_x3, "jump_vaddr_x3"},
  {(intptr_t)jump_vaddr_x4, "jump_vaddr_x4"},
  {(intptr_t)jump_vaddr_x5, "jump_vaddr_x5"},
  {(intptr_t)jump_vaddr_x6, "jump_vaddr_x6"},
  {(intptr_t)jump_vaddr_x7, "jump_vaddr_x7"},
  {(intptr_t)jump_vaddr_x8, "jump_vaddr_x8"},
  {(intptr_t)jump_vaddr_x9, "jump_vaddr_x9"},
  {(intptr_t)jump_vaddr_x10, "jump_vaddr_x10"},
  {(intptr_t)jump_vaddr_x11, "jump_vaddr_x11"},
  {(intptr_t)jump_vaddr_x12, "jump_vaddr_x12"},
  {(intptr_t)jump_vaddr_x13, "jump_vaddr_x13"},
  {(intptr_t)jump_vaddr_x14, "jump_vaddr_x14"},
  {(intptr_t)jump_vaddr_x15, "jump_vaddr_x15"},
  {(intptr_t)jump_vaddr_x16, "jump_vaddr_x16"},
  {(intptr_t)jump_vaddr_x17, "jump_vaddr_x17"},
  {(intptr_t)jump_vaddr_x18, "jump_vaddr_x18"},
  {(intptr_t)jump_vaddr_x19, "jump_vaddr_x19"},
  {(intptr_t)jump_vaddr_x20, "jump_vaddr_x20"},
  {(intptr_t)jump_vaddr_x21, "jump_vaddr_x21"},
  {(intptr_t)jump_vaddr_x22, "jump_vaddr_x22"},
  {(intptr_t)jump_vaddr_x23, "jump_vaddr_x23"},
  {(intptr_t)jump_vaddr_x24, "jump_vaddr_x24"},
  {(intptr_t)jump_vaddr_x25, "jump_vaddr_x25"},
  {(intptr_t)jump_vaddr_x26, "jump_vaddr_x26"},
  {(intptr_t)jump_vaddr_x27, "jump_vaddr_x27"},
  {(intptr_t)jump_vaddr_x28, "jump_vaddr_x28"},
  {(intptr_t)invalidate_addr_x0," invalidate_addr_x0"},
  {(intptr_t)invalidate_addr_x1," invalidate_addr_x1"},
  {(intptr_t)invalidate_addr_x2," invalidate_addr_x2"},
  {(intptr_t)invalidate_addr_x3," invalidate_addr_x3"},
  {(intptr_t)invalidate_addr_x4," invalidate_addr_x4"},
  {(intptr_t)invalidate_addr_x5," invalidate_addr_x5"},
  {(intptr_t)invalidate_addr_x6," invalidate_addr_x6"},
  {(intptr_t)invalidate_addr_x7," invalidate_addr_x7"},
  {(intptr_t)invalidate_addr_x8," invalidate_addr_x8"},
  {(intptr_t)invalidate_addr_x9," invalidate_addr_x9"},
  {(intptr_t)invalidate_addr_x10," invalidate_addr_x10"},
  {(intptr_t)invalidate_addr_x11," invalidate_addr_x11"},
  {(intptr_t)invalidate_addr_x12," invalidate_addr_x12"},
  {(intptr_t)invalidate_addr_x13," invalidate_addr_x13"},
  {(intptr_t)invalidate_addr_x14," invalidate_addr_x14"},
  {(intptr_t)invalidate_addr_x15," invalidate_addr_x15"},
  {(intptr_t)invalidate_addr_x16," invalidate_addr_x16"},
  {(intptr_t)invalidate_addr_x17," invalidate_addr_x17"},
  {(intptr_t)invalidate_addr_x18," invalidate_addr_x18"},
  {(intptr_t)invalidate_addr_x19," invalidate_addr_x19"},
  {(intptr_t)invalidate_addr_x20," invalidate_addr_x20"},
  {(intptr_t)invalidate_addr_x21," invalidate_addr_x21"},
  {(intptr_t)invalidate_addr_x22," invalidate_addr_x22"},
  {(intptr_t)invalidate_addr_x23," invalidate_addr_x23"},
  {(intptr_t)invalidate_addr_x24," invalidate_addr_x24"},
  {(intptr_t)invalidate_addr_x25," invalidate_addr_x25"},
  {(intptr_t)invalidate_addr_x26," invalidate_addr_x26"},
  {(intptr_t)invalidate_addr_x27," invalidate_addr_x27"},
  {(intptr_t)invalidate_addr_x28," invalidate_addr_x28"},
#else
  {(intptr_t)jump_vaddr_r0, "jump_vaddr_r0"},
  {(intptr_t)jump_vaddr_r1, "jump_vaddr_r1"},
  {(intptr_t)jump_vaddr_r2, "jump_vaddr_r2"},
  {(intptr_t)jump_vaddr_r3, "jump_vaddr_r3"},
  {(intptr_t)jump_vaddr_r4, "jump_vaddr_r4"},
  {(intptr_t)jump_vaddr_r5, "jump_vaddr_r5"},
  {(intptr_t)jump_vaddr_r6, "jump_vaddr_r6"},
  {(intptr_t)jump_vaddr_r7, "jump_vaddr_r7"},
  {(intptr_t)jump_vaddr_r8, "jump_vaddr_r8"},
  {(intptr_t)jump_vaddr_r9, "jump_vaddr_r9"},
  {(intptr_t)jump_vaddr_r10, "jump_vaddr_r10"},
  {(intptr_t)jump_vaddr_r12, "jump_vaddr_r12"},
  {(intptr_t)invalidate_addr_r0," invalidate_addr_r0"},
  {(intptr_t)invalidate_addr_r1," invalidate_addr_r1"},
  {(intptr_t)invalidate_addr_r2," invalidate_addr_r2"},
  {(intptr_t)invalidate_addr_r3," invalidate_addr_r3"},
  {(intptr_t)invalidate_addr_r4," invalidate_addr_r4"},
  {(intptr_t)invalidate_addr_r5," invalidate_addr_r5"},
  {(intptr_t)invalidate_addr_r6," invalidate_addr_r6"},
  {(intptr_t)invalidate_addr_r7," invalidate_addr_r7"},
  {(intptr_t)invalidate_addr_r8," invalidate_addr_r8"},
  {(intptr_t)invalidate_addr_r9," invalidate_addr_r9"},
  {(intptr_t)invalidate_addr_r10," invalidate_addr_r10"},
  {(intptr_t)invalidate_addr_r12," invalidate_addr_r12"},
#endif
#else
  {(intptr_t)jump_vaddr_eax, "jump_vaddr_eax"},
  {(intptr_t)jump_vaddr_ecx, "jump_vaddr_ecx"},
  {(intptr_t)jump_vaddr_edx, "jump_vaddr_edx"},
  {(intptr_t)jump_vaddr_ebx, "jump_vaddr_ebx"},
  {(intptr_t)jump_vaddr_ebp, "jump_vaddr_ebp"},
  {(intptr_t)jump_vaddr_edi, "jump_vaddr_edi"},
  {(intptr_t)invalidate_block_eax, "invalidate_block_eax"},
  {(intptr_t)invalidate_block_ecx, "invalidate_block_ecx"},
  {(intptr_t)invalidate_block_edx, "invalidate_block_edx"},
  {(intptr_t)invalidate_block_ebx, "invalidate_block_ebx"},
  {(intptr_t)invalidate_block_ebp, "invalidate_block_ebp"},
  {(intptr_t)invalidate_block_esi, "invalidate_block_esi"},
  {(intptr_t)invalidate_block_edi, "invalidate_block_edi"},
#endif
  {(intptr_t)dynamic_linker, "dynamic_linker"},
  {(intptr_t)dynamic_linker_ds, "dynamic_linker_ds"},
  {(intptr_t)TLBWI_new, "TLBWI_new"},
  {(intptr_t)TLBWR_new, "TLBWR_new"},
  {(intptr_t)verify_code, "verify_code"},
  {(intptr_t)verify_code_vm, "verify_code_vm"},
  {(intptr_t)verify_code_ds, "verify_code_ds"},
  {(intptr_t)cc_interrupt, "cc_interrupt"},
  {(intptr_t)fp_exception, "fp_exception"},
  {(intptr_t)fp_exception_ds, "fp_exception_ds"},
  {(intptr_t)jump_syscall, "jump_syscall"},
  {(intptr_t)jump_eret, "jump_eret"},
  {(intptr_t)do_interrupt, "do_interrupt"},
  {(intptr_t)div64, "div64"},
  {(intptr_t)divu64, "divu64"},
  {(intptr_t)cvt_s_w, "cvt_s_w"},
  {(intptr_t)cvt_d_w, "cvt_d_w"},
  {(intptr_t)cvt_s_l, "cvt_s_l"},
  {(intptr_t)cvt_d_l, "cvt_d_l"},
  {(intptr_t)cvt_w_s, "cvt_w_s"},
  {(intptr_t)cvt_w_d, "cvt_w_d"},
  {(intptr_t)cvt_l_s, "cvt_l_s"},
  {(intptr_t)cvt_l_d, "cvt_l_d"},
  {(intptr_t)cvt_d_s, "cvt_d_s"},
  {(intptr_t)cvt_s_d, "cvt_s_d"},
  {(intptr_t)round_l_s, "round_l_s"},
  {(intptr_t)round_w_s, "round_w_s"},
  {(intptr_t)trunc_l_s, "trunc_l_s"},
  {(intptr_t)trunc_w_s, "trunc_w_s"},
  {(intptr_t)ceil_l_s, "ceil_l_s"},
  {(intptr_t)ceil_w_s, "ceil_w_s"},
  {(intptr_t)floor_l_s, "floor_l_s"},
  {(intptr_t)floor_w_s, "floor_w_s"},
  {(intptr_t)round_l_d, "round_l_d"},
  {(intptr_t)round_w_d, "round_w_d"},
  {(intptr_t)trunc_l_d, "trunc_l_d"},
  {(intptr_t)trunc_w_d, "trunc_w_d"},
  {(intptr_t)ceil_l_d, "ceil_l_d"},
  {(intptr_t)ceil_w_d, "ceil_w_d"},
  {(intptr_t)floor_l_d, "floor_l_d"},
  {(intptr_t)floor_w_d, "floor_w_d"},
  {(intptr_t)c_f_s, "c_f_s"},
  {(intptr_t)c_un_s, "c_un_s"},
  {(intptr_t)c_eq_s, "c_eq_s"},
  {(intptr_t)c_ueq_s, "c_ueq_s"},
  {(intptr_t)c_olt_s, "c_olt_s"},
  {(intptr_t)c_ult_s, "c_ult_s"},
  {(intptr_t)c_ole_s, "c_ole_s"},
  {(intptr_t)c_ule_s, "c_ule_s"},
  {(intptr_t)c_sf_s, "c_sf_s"},
  {(intptr_t)c_ngle_s, "c_ngle_s"},
  {(intptr_t)c_seq_s, "c_seq_s"},
  {(intptr_t)c_ngl_s, "c_ngl_s"},
  {(intptr_t)c_lt_s, "c_lt_s"},
  {(intptr_t)c_nge_s, "c_nge_s"},
  {(intptr_t)c_le_s, "c_le_s"},
  {(intptr_t)c_ngt_s, "c_ngt_s"},
  {(intptr_t)c_f_d, "c_f_d"},
  {(intptr_t)c_un_d, "c_un_d"},
  {(intptr_t)c_eq_d, "c_eq_d"},
  {(intptr_t)c_ueq_d, "c_ueq_d"},
  {(intptr_t)c_olt_d, "c_olt_d"},
  {(intptr_t)c_ult_d, "c_ult_d"},
  {(intptr_t)c_ole_d, "c_ole_d"},
  {(intptr_t)c_ule_d, "c_ule_d"},
  {(intptr_t)c_sf_d, "c_sf_d"},
  {(intptr_t)c_ngle_d, "c_ngle_d"},
  {(intptr_t)c_seq_d, "c_seq_d"},
  {(intptr_t)c_ngl_d, "c_ngl_d"},
  {(intptr_t)c_lt_d, "c_lt_d"},
  {(intptr_t)c_nge_d, "c_nge_d"},
  {(intptr_t)c_le_d, "c_le_d"},
  {(intptr_t)c_ngt_d, "c_ngt_d"},
  {(intptr_t)add_s, "add_s"},
  {(intptr_t)sub_s, "sub_s"},
  {(intptr_t)mul_s, "mul_s"},
  {(intptr_t)div_s, "div_s"},
  {(intptr_t)sqrt_s, "sqrt_s"},
  {(intptr_t)abs_s, "abs_s"},
  {(intptr_t)mov_s, "mov_s"},
  {(intptr_t)neg_s, "neg_s"},
  {(intptr_t)add_d, "add_d"},
  {(intptr_t)sub_d, "sub_d"},
  {(intptr_t)mul_d, "mul_d"},
  {(intptr_t)div_d, "div_d"},
  {(intptr_t)sqrt_d, "sqrt_d"},
  {(intptr_t)abs_d, "abs_d"},
  {(intptr_t)mov_d, "mov_d"},
  {(intptr_t)neg_d, "neg_d"},
  {-1, NULL}
};

#undef address
#undef reg

static FILE * pFile;
static csh handle;

void profiler_init(void)
{
  if(cs_open(ARCHITECTURE, MODE, &handle) != CS_ERR_OK) return;
  cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
  base_addr = extra_memory;
  new_dynarec_init();

  func[0].addr = (uintptr_t)cached_interpreter_table.MFC0;
  func[1].addr = (uintptr_t)cached_interpreter_table.MTC0;
  func[2].addr = (uintptr_t)cached_interpreter_table.TLBR;
  func[3].addr = (uintptr_t)cached_interpreter_table.TLBP;
}

void profiler_cleanup(void)
{
  new_dynarec_cleanup();
  if(handle == 0) return;
  cs_close(&handle);
}

void profiler_block(int addr)
{
  uint32_t * beginning;
  uint32_t * end;
  cs_insn *insn;
  size_t count;
  int32_t size = 0;
  int32_t sum = 0;
  char filename[16];

  beginning=(uint32_t *)out;
  new_recompile_block(addr);
  end=(uint32_t *)out;

  //for(int i=0;i<linkcount;i++){
  //  if(!link_addr[i][2])
  //    dynamic_linker((void*)link_addr[i][0],0xa4000044);
  //}

  //int i;
  //for(i = 0; i < 4096; i++)
  //{
  //  struct ll_entry *head;
  //  head=jump_out[i];
  //  while(head!=NULL) {
  //    intptr_t addr=get_pointer(head->addr);
  //    addr=(intptr_t)kill_pointer(head->addr);
  //    head=head->next;
  //  }

  //  head=jump_dirty[i];
  //  while(head!=NULL) {
  //    verify_dirty(head->addr);
  //    uintptr_t start,end;
  //    get_bounds((intptr_t)head->addr, &start, &end);
  //    isclean((intptr_t)head->addr);
  //    uintptr_t clean=get_clean_addr((intptr_t)head->addr);
  //    head=head->next;
  //  }

  //  head=jump_in[i];
  //  while(head!=NULL) {
  //    isclean((intptr_t)head->addr);
  //    head=head->next;
  //  }
  //}

#ifdef DISASM_BLOCK
  int debug=0;
  int block, inst;
  for(block=0;block<(sizeof(disasm_block)>>2);block++) {
    for(inst=0;inst<slen;inst++) {
      if((start+inst*4)==disasm_block[block]) {
        debug=1;
        break;
      }
    }
  }
  if(!debug) return;
#else
  return;
#endif

  if(handle == 0) return;

  sprintf(filename, "%.8x.txt", addr);
  pFile = fopen (filename,"w");
  size = (intptr_t)end - (intptr_t)beginning;
  size = (size < 0) ? (-size) : size;

  count = cs_disasm(handle, (uint8_t*)beginning, size, (uintptr_t)beginning, 0, &insn);
  if(count <= 0) return;

  for (uint32_t i = 0; i < count; i++) {
    sum += insn[i].size;
 #if NEW_DYNAREC_PROFILER >= NEW_DYNAREC_ARM
    if(INSTRUCTION.operands[1].reg == FP_REGISTER) {
      uint32_t j = 0;
      uint32_t imm;

      if(INSTRUCTION.op_count > 2)
        imm = INSTRUCTION.operands[2].mem.base;
      else
        imm = INSTRUCTION.operands[1].mem.disp;

      assert(imm>=0 && imm<4096);

      while(var[j].addr != -1) {
        uint32_t offset = var[j].addr - (uintptr_t)&dynarec_local;
        if(imm >= offset && imm < (offset + var[j].size))
          break;
        j++;
      }
      if(var[j].addr != -1) {
        fprintf(pFile, "0x%x: %s %s (%s+%d)\n", (uintptr_t)insn[i].address, insn[i].mnemonic, insn[i].op_str, var[j].name, imm - (var[j].addr - (uintptr_t)&dynarec_local));
        continue;
      }
    }
#else
    // TODO: x86
#endif

    if(insn[i].id == CALL_INST) {
      uint32_t j = 0;
      intptr_t addr = INSTRUCTION.operands[0].imm;

      while(func[j].addr != -1) {
        if(addr == func[j].addr)
          break;
        j++;
      }
      if(func[j].addr != -1) {
        fprintf(pFile, "0x%x: %s %s (%s)\n", (uintptr_t)insn[i].address, insn[i].mnemonic, insn[i].op_str, func[j].name);
        continue;
      }
    }
    fprintf(pFile, "0x%x: %s %s\n", (uintptr_t)insn[i].address, insn[i].mnemonic, insn[i].op_str);
  }

  if(size != sum)
    fprintf(pFile, "Failed to disassemble code at: 0x%.8x\n", (uintptr_t)beginning + sum);

  cs_free(insn, count);
  fflush(pFile);
  fclose(pFile);
}

void set_tlb(void)
{
  using_tlb = 1;
}

void copy_mapping(void * map)
{
  memcpy((void*)memory_map, map, sizeof(memory_map));
}

#endif