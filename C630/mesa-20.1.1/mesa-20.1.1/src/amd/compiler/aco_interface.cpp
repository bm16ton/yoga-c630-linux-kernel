/*
 * Copyright © 2018 Google
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "aco_interface.h"
#include "aco_ir.h"
#include "vulkan/radv_shader.h"
#include "vulkan/radv_shader_args.h"
#include "c11/threads.h"
#include "util/debug.h"

#include <iostream>
#include <sstream>

namespace aco {
uint64_t debug_flags = 0;

static const struct debug_control aco_debug_options[] = {
   {"validateir", DEBUG_VALIDATE},
   {"validatera", DEBUG_VALIDATE_RA},
   {"perfwarn", DEBUG_PERFWARN},
   {NULL, 0}
};

static once_flag init_once_flag = ONCE_FLAG_INIT;

static void init()
{
   debug_flags = parse_debug_string(getenv("ACO_DEBUG"), aco_debug_options);

   #ifndef NDEBUG
   /* enable some flags by default on debug builds */
   debug_flags |= aco::DEBUG_VALIDATE;
   #endif
}
}

static radv_compiler_statistic_info statistic_infos[] = {
   [aco::statistic_hash] = {"Hash", "CRC32 hash of code and constant data"},
   [aco::statistic_instructions] = {"Instructions", "Instruction count"},
   [aco::statistic_copies] = {"Copies", "Copy instructions created for pseudo-instructions"},
   [aco::statistic_branches] = {"Branches", "Branch instructions"},
   [aco::statistic_cycles] = {"Busy Cycles", "Estimate of busy cycles"},
   [aco::statistic_vmem_clauses] = {"VMEM Clause", "Number of VMEM clauses (includes 1-sized clauses)"},
   [aco::statistic_smem_clauses] = {"SMEM Clause", "Number of SMEM clauses (includes 1-sized clauses)"},
   [aco::statistic_vmem_score] = {"VMEM Score", "Average VMEM def-use distances"},
   [aco::statistic_smem_score] = {"SMEM Score", "Average SMEM def-use distances"},
   [aco::statistic_sgpr_presched] = {"Pre-Sched SGPRs", "SGPR usage before scheduling"},
   [aco::statistic_vgpr_presched] = {"Pre-Sched VGPRs", "VGPR usage before scheduling"},
};

void aco_compile_shader(unsigned shader_count,
                        struct nir_shader *const *shaders,
                        struct radv_shader_binary **binary,
                        struct radv_shader_args *args)
{
   call_once(&aco::init_once_flag, aco::init);

   ac_shader_config config = {0};
   std::unique_ptr<aco::Program> program{new aco::Program};

   program->collect_statistics = args->options->record_stats;
   if (program->collect_statistics)
      memset(program->statistics, 0, sizeof(program->statistics));

   /* Instruction Selection */
   if (args->is_gs_copy_shader)
      aco::select_gs_copy_shader(program.get(), shaders[0], &config, args);
   else
      aco::select_program(program.get(), shader_count, shaders, &config, args);
   if (args->options->dump_preoptir) {
      std::cerr << "After Instruction Selection:\n";
      aco_print_program(program.get(), stderr);
   }
   aco::validate(program.get(), stderr);

   /* Phi lowering */
   aco::lower_phis(program.get());
   //std::cerr << "After Phi Lowering:\n";
   //aco_print_program(program.get(), stderr);

   aco::dominator_tree(program.get());

   /* Optimization */
   aco::value_numbering(program.get());
   aco::optimize(program.get());
   aco::validate(program.get(), stderr);

   aco::setup_reduce_temp(program.get());
   aco::insert_exec_mask(program.get());
   aco::validate(program.get(), stderr);

   aco::live live_vars = aco::live_var_analysis(program.get(), args->options);
   aco::spill(program.get(), live_vars, args->options);

   if (program->collect_statistics)
      aco::collect_presched_stats(program.get());

   //std::cerr << "Before Schedule:\n";
   //aco_print_program(program.get(), stderr);
   aco::schedule_program(program.get(), live_vars);

   std::string llvm_ir;
   if (args->options->record_ir) {
      char *data = NULL;
      size_t size = 0;
      FILE *f = open_memstream(&data, &size);
      if (f) {
         aco_print_program(program.get(), f);
         fputc(0, f);
         fclose(f);
      }

      llvm_ir = std::string(data, data + size);
      free(data);
   }

   /* Register Allocation */
   aco::register_allocation(program.get(), live_vars.live_out);
   if (args->options->dump_shader) {
      std::cerr << "After RA:\n";
      aco_print_program(program.get(), stderr);
   }

   if (aco::validate_ra(program.get(), args->options, stderr)) {
      std::cerr << "Program after RA validation failure:\n";
      aco_print_program(program.get(), stderr);
      abort();
   }

   aco::ssa_elimination(program.get());
   /* Lower to HW Instructions */
   aco::lower_to_hw_instr(program.get());
   //std::cerr << "After Eliminate Pseudo Instr:\n";
   //aco_print_program(program.get(), stderr);

   /* Insert Waitcnt */
   aco::insert_wait_states(program.get());
   aco::insert_NOPs(program.get());

   //std::cerr << "After Insert-Waitcnt:\n";
   //aco_print_program(program.get(), stderr);

   if (program->collect_statistics)
      aco::collect_preasm_stats(program.get());

   /* Assembly */
   std::vector<uint32_t> code;
   unsigned exec_size = aco::emit_program(program.get(), code);

   if (program->collect_statistics)
      aco::collect_postasm_stats(program.get(), code);

   bool get_disasm = args->options->dump_shader || args->options->record_ir;

   size_t size = llvm_ir.size();

   std::string disasm;
   if (get_disasm) {
      std::ostringstream stream;
      aco::print_asm(program.get(), code, exec_size / 4u, stream);
      stream << '\0';
      disasm = stream.str();
      size += disasm.size();
   }

   size_t stats_size = 0;
   if (program->collect_statistics)
      stats_size = sizeof(radv_compiler_statistics) + aco::num_statistics * sizeof(uint32_t);
   size += stats_size;

   size += code.size() * sizeof(uint32_t) + sizeof(radv_shader_binary_legacy);
   /* We need to calloc to prevent unintialized data because this will be used
    * directly for the disk cache. Uninitialized data can appear because of
    * padding in the struct or because legacy_binary->data can be at an offset
    * from the start less than sizeof(radv_shader_binary_legacy). */
   radv_shader_binary_legacy* legacy_binary = (radv_shader_binary_legacy*) calloc(size, 1);

   legacy_binary->base.type = RADV_BINARY_TYPE_LEGACY;
   legacy_binary->base.stage = shaders[shader_count-1]->info.stage;
   legacy_binary->base.is_gs_copy_shader = args->is_gs_copy_shader;
   legacy_binary->base.total_size = size;

   if (program->collect_statistics) {
      radv_compiler_statistics *statistics = (radv_compiler_statistics *)legacy_binary->data;
      statistics->count = aco::num_statistics;
      statistics->infos = statistic_infos;
      memcpy(statistics->values, program->statistics, aco::num_statistics * sizeof(uint32_t));
   }
   legacy_binary->stats_size = stats_size;

   memcpy(legacy_binary->data + legacy_binary->stats_size, code.data(), code.size() * sizeof(uint32_t));
   legacy_binary->exec_size = exec_size;
   legacy_binary->code_size = code.size() * sizeof(uint32_t);

   legacy_binary->config = config;
   legacy_binary->disasm_size = 0;
   legacy_binary->ir_size = llvm_ir.size();

   llvm_ir.copy((char*) legacy_binary->data + legacy_binary->stats_size + legacy_binary->code_size, llvm_ir.size());

   if (get_disasm) {
      disasm.copy((char*) legacy_binary->data + legacy_binary->stats_size + legacy_binary->code_size + llvm_ir.size(), disasm.size());
      legacy_binary->disasm_size = disasm.size();
   }

   *binary = (radv_shader_binary*) legacy_binary;
}
