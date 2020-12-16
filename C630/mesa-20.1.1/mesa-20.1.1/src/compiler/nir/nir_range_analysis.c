/*
 * Copyright © 2018 Intel Corporation
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
#include <math.h>
#include <float.h>
#include "nir.h"
#include "nir_range_analysis.h"
#include "util/hash_table.h"

/**
 * Analyzes a sequence of operations to determine some aspects of the range of
 * the result.
 */

static bool
is_not_negative(enum ssa_ranges r)
{
   return r == gt_zero || r == ge_zero || r == eq_zero;
}

static void *
pack_data(const struct ssa_result_range r)
{
   return (void *)(uintptr_t)(r.range | r.is_integral << 8);
}

static struct ssa_result_range
unpack_data(const void *p)
{
   const uintptr_t v = (uintptr_t) p;

   return (struct ssa_result_range){v & 0xff, (v & 0x0ff00) != 0};
}

static void *
pack_key(const struct nir_alu_instr *instr, nir_alu_type type)
{
   uintptr_t type_encoding;
   uintptr_t ptr = (uintptr_t) instr;

   /* The low 2 bits have to be zero or this whole scheme falls apart. */
   assert((ptr & 0x3) == 0);

   /* NIR is typeless in the sense that sequences of bits have whatever
    * meaning is attached to them by the instruction that consumes them.
    * However, the number of bits must match between producer and consumer.
    * As a result, the number of bits does not need to be encoded here.
    */
   switch (nir_alu_type_get_base_type(type)) {
   case nir_type_int:   type_encoding = 0; break;
   case nir_type_uint:  type_encoding = 1; break;
   case nir_type_bool:  type_encoding = 2; break;
   case nir_type_float: type_encoding = 3; break;
   default: unreachable("Invalid base type.");
   }

   return (void *)(ptr | type_encoding);
}

static nir_alu_type
nir_alu_src_type(const nir_alu_instr *instr, unsigned src)
{
   return nir_alu_type_get_base_type(nir_op_infos[instr->op].input_types[src]) |
          nir_src_bit_size(instr->src[src].src);
}

static struct ssa_result_range
analyze_constant(const struct nir_alu_instr *instr, unsigned src,
                 nir_alu_type use_type)
{
   uint8_t swizzle[4] = { 0, 1, 2, 3 };

   /* If the source is an explicitly sized source, then we need to reset
    * both the number of components and the swizzle.
    */
   const unsigned num_components = nir_ssa_alu_instr_src_components(instr, src);

   for (unsigned i = 0; i < num_components; ++i)
      swizzle[i] = instr->src[src].swizzle[i];

   const nir_load_const_instr *const load =
      nir_instr_as_load_const(instr->src[src].src.ssa->parent_instr);

   struct ssa_result_range r = { unknown, false };

   switch (nir_alu_type_get_base_type(use_type)) {
   case nir_type_float: {
      double min_value = DBL_MAX;
      double max_value = -DBL_MAX;
      bool any_zero = false;
      bool all_zero = true;

      r.is_integral = true;

      for (unsigned i = 0; i < num_components; ++i) {
         const double v = nir_const_value_as_float(load->value[swizzle[i]],
                                                   load->def.bit_size);

         if (floor(v) != v)
            r.is_integral = false;

         any_zero = any_zero || (v == 0.0);
         all_zero = all_zero && (v == 0.0);
         min_value = MIN2(min_value, v);
         max_value = MAX2(max_value, v);
      }

      assert(any_zero >= all_zero);
      assert(isnan(max_value) || max_value >= min_value);

      if (all_zero)
         r.range = eq_zero;
      else if (min_value > 0.0)
         r.range = gt_zero;
      else if (min_value == 0.0)
         r.range = ge_zero;
      else if (max_value < 0.0)
         r.range = lt_zero;
      else if (max_value == 0.0)
         r.range = le_zero;
      else if (!any_zero)
         r.range = ne_zero;
      else
         r.range = unknown;

      return r;
   }

   case nir_type_int:
   case nir_type_bool: {
      int64_t min_value = INT_MAX;
      int64_t max_value = INT_MIN;
      bool any_zero = false;
      bool all_zero = true;

      for (unsigned i = 0; i < num_components; ++i) {
         const int64_t v = nir_const_value_as_int(load->value[swizzle[i]],
                                                  load->def.bit_size);

         any_zero = any_zero || (v == 0);
         all_zero = all_zero && (v == 0);
         min_value = MIN2(min_value, v);
         max_value = MAX2(max_value, v);
      }

      assert(any_zero >= all_zero);
      assert(max_value >= min_value);

      if (all_zero)
         r.range = eq_zero;
      else if (min_value > 0)
         r.range = gt_zero;
      else if (min_value == 0)
         r.range = ge_zero;
      else if (max_value < 0)
         r.range = lt_zero;
      else if (max_value == 0)
         r.range = le_zero;
      else if (!any_zero)
         r.range = ne_zero;
      else
         r.range = unknown;

      return r;
   }

   case nir_type_uint: {
      bool any_zero = false;
      bool all_zero = true;

      for (unsigned i = 0; i < num_components; ++i) {
         const uint64_t v = nir_const_value_as_uint(load->value[swizzle[i]],
                                                    load->def.bit_size);

         any_zero = any_zero || (v == 0);
         all_zero = all_zero && (v == 0);
      }

      assert(any_zero >= all_zero);

      if (all_zero)
         r.range = eq_zero;
      else if (any_zero)
         r.range = ge_zero;
      else
         r.range = gt_zero;

      return r;
   }

   default:
      unreachable("Invalid alu source type");
   }
}

/**
 * Short-hand name for use in the tables in analyze_expression.  If this name
 * becomes a problem on some compiler, we can change it to _.
 */
#define _______ unknown


#if defined(__clang__)
   /* clang wants _Pragma("unroll X") */
   #define pragma_unroll_5 _Pragma("unroll 5")
   #define pragma_unroll_7 _Pragma("unroll 7")
/* gcc wants _Pragma("GCC unroll X") */
#elif defined(__GNUC__)
   #if __GNUC__ >= 8
      #define pragma_unroll_5 _Pragma("GCC unroll 5")
      #define pragma_unroll_7 _Pragma("GCC unroll 7")
   #else
      #pragma GCC optimize ("unroll-loops")
      #define pragma_unroll_5
      #define pragma_unroll_7
   #endif
#else
   /* MSVC doesn't have C99's _Pragma() */
   #define pragma_unroll_5
   #define pragma_unroll_7
#endif


#ifndef NDEBUG
#define ASSERT_TABLE_IS_COMMUTATIVE(t)                        \
   do {                                                       \
      static bool first = true;                               \
      if (first) {                                            \
         first = false;                                       \
         pragma_unroll_7                                      \
         for (unsigned r = 0; r < ARRAY_SIZE(t); r++) {       \
            pragma_unroll_7                                   \
            for (unsigned c = 0; c < ARRAY_SIZE(t[0]); c++)   \
               assert(t[r][c] == t[c][r]);                    \
         }                                                    \
      }                                                       \
   } while (false)

#define ASSERT_TABLE_IS_DIAGONAL(t)                           \
   do {                                                       \
      static bool first = true;                               \
      if (first) {                                            \
         first = false;                                       \
         pragma_unroll_7                                      \
         for (unsigned r = 0; r < ARRAY_SIZE(t); r++)         \
            assert(t[r][r] == r);                             \
      }                                                       \
   } while (false)

static enum ssa_ranges
union_ranges(enum ssa_ranges a, enum ssa_ranges b)
{
   static const enum ssa_ranges union_table[last_range + 1][last_range + 1] = {
      /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
      /* unknown */ { _______, _______, _______, _______, _______, _______, _______ },
      /* lt_zero */ { _______, lt_zero, le_zero, ne_zero, _______, ne_zero, le_zero },
      /* le_zero */ { _______, le_zero, le_zero, _______, _______, _______, le_zero },
      /* gt_zero */ { _______, ne_zero, _______, gt_zero, ge_zero, ne_zero, ge_zero },
      /* ge_zero */ { _______, _______, _______, ge_zero, ge_zero, _______, ge_zero },
      /* ne_zero */ { _______, ne_zero, _______, ne_zero, _______, ne_zero, _______ },
      /* eq_zero */ { _______, le_zero, le_zero, ge_zero, ge_zero, _______, eq_zero },
   };

   ASSERT_TABLE_IS_COMMUTATIVE(union_table);
   ASSERT_TABLE_IS_DIAGONAL(union_table);

   return union_table[a][b];
}

/* Verify that the 'unknown' entry in each row (or column) of the table is the
 * union of all the other values in the row (or column).
 */
#define ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_2_SOURCE(t)              \
   do {                                                                 \
      static bool first = true;                                         \
      if (first) {                                                      \
         first = false;                                                 \
         pragma_unroll_7                                                \
         for (unsigned i = 0; i < last_range; i++) {                    \
            enum ssa_ranges col_range = t[i][unknown + 1];              \
            enum ssa_ranges row_range = t[unknown + 1][i];              \
                                                                        \
            pragma_unroll_5                                             \
            for (unsigned j = unknown + 2; j < last_range; j++) {       \
               col_range = union_ranges(col_range, t[i][j]);            \
               row_range = union_ranges(row_range, t[j][i]);            \
            }                                                           \
                                                                        \
            assert(col_range == t[i][unknown]);                         \
            assert(row_range == t[unknown][i]);                         \
         }                                                              \
      }                                                                 \
   } while (false)

/* For most operations, the union of ranges for a strict inequality and
 * equality should be the range of the non-strict inequality (e.g.,
 * union_ranges(range(op(lt_zero), range(op(eq_zero))) == range(op(le_zero)).
 *
 * Does not apply to selection-like opcodes (bcsel, fmin, fmax, etc.).
 */
#define ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_1_SOURCE(t) \
   do {                                                                 \
      assert(union_ranges(t[lt_zero], t[eq_zero]) == t[le_zero]);       \
      assert(union_ranges(t[gt_zero], t[eq_zero]) == t[ge_zero]);       \
   } while (false)

#define ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_2_SOURCE(t) \
   do {                                                                 \
      static bool first = true;                                         \
      if (first) {                                                      \
         first = false;                                                 \
         pragma_unroll_7                                                \
         for (unsigned i = 0; i < last_range; i++) {                    \
            assert(union_ranges(t[i][lt_zero], t[i][eq_zero]) == t[i][le_zero]); \
            assert(union_ranges(t[i][gt_zero], t[i][eq_zero]) == t[i][ge_zero]); \
            assert(union_ranges(t[lt_zero][i], t[eq_zero][i]) == t[le_zero][i]); \
            assert(union_ranges(t[gt_zero][i], t[eq_zero][i]) == t[ge_zero][i]); \
         }                                                              \
      }                                                                 \
   } while (false)

/* Several other unordered tuples span the range of "everything."  Each should
 * have the same value as unknown: (lt_zero, ge_zero), (le_zero, gt_zero), and
 * (eq_zero, ne_zero).  union_ranges is already commutative, so only one
 * ordering needs to be checked.
 *
 * Does not apply to selection-like opcodes (bcsel, fmin, fmax, etc.).
 *
 * In cases where this can be used, it is unnecessary to also use
 * ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_*_SOURCE.  For any range X,
 * union_ranges(X, X) == X.  The disjoint ranges cover all of the non-unknown
 * possibilities, so the union of all the unions of disjoint ranges is
 * equivalent to the union of "others."
 */
#define ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_1_SOURCE(t)            \
   do {                                                                 \
      assert(union_ranges(t[lt_zero], t[ge_zero]) == t[unknown]);       \
      assert(union_ranges(t[le_zero], t[gt_zero]) == t[unknown]);       \
      assert(union_ranges(t[eq_zero], t[ne_zero]) == t[unknown]);       \
   } while (false)

#define ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_2_SOURCE(t)            \
   do {                                                                 \
      static bool first = true;                                         \
      if (first) {                                                      \
         first = false;                                                 \
         pragma_unroll_7                                                \
         for (unsigned i = 0; i < last_range; i++) {                    \
            assert(union_ranges(t[i][lt_zero], t[i][ge_zero]) ==        \
                   t[i][unknown]);                                      \
            assert(union_ranges(t[i][le_zero], t[i][gt_zero]) ==        \
                   t[i][unknown]);                                      \
            assert(union_ranges(t[i][eq_zero], t[i][ne_zero]) ==        \
                   t[i][unknown]);                                      \
                                                                        \
            assert(union_ranges(t[lt_zero][i], t[ge_zero][i]) ==        \
                   t[unknown][i]);                                      \
            assert(union_ranges(t[le_zero][i], t[gt_zero][i]) ==        \
                   t[unknown][i]);                                      \
            assert(union_ranges(t[eq_zero][i], t[ne_zero][i]) ==        \
                   t[unknown][i]);                                      \
         }                                                              \
      }                                                                 \
   } while (false)

#else
#define ASSERT_TABLE_IS_COMMUTATIVE(t)
#define ASSERT_TABLE_IS_DIAGONAL(t)
#define ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_2_SOURCE(t)
#define ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_1_SOURCE(t)
#define ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_2_SOURCE(t)
#define ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_1_SOURCE(t)
#define ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_2_SOURCE(t)
#endif

/**
 * Analyze an expression to determine the range of its result
 *
 * The end result of this analysis is a token that communicates something
 * about the range of values.  There's an implicit grammar that produces
 * tokens from sequences of literal values, other tokens, and operations.
 * This function implements this grammar as a recursive-descent parser.  Some
 * (but not all) of the grammar is listed in-line in the function.
 */
static struct ssa_result_range
analyze_expression(const nir_alu_instr *instr, unsigned src,
                   struct hash_table *ht, nir_alu_type use_type)
{
   /* Ensure that the _Pragma("GCC unroll 7") above are correct. */
   STATIC_ASSERT(last_range + 1 == 7);

   if (!instr->src[src].src.is_ssa)
      return (struct ssa_result_range){unknown, false};

   if (nir_src_is_const(instr->src[src].src))
      return analyze_constant(instr, src, use_type);

   if (instr->src[src].src.ssa->parent_instr->type != nir_instr_type_alu)
      return (struct ssa_result_range){unknown, false};

   const struct nir_alu_instr *const alu =
       nir_instr_as_alu(instr->src[src].src.ssa->parent_instr);

   /* Bail if the type of the instruction generating the value does not match
    * the type the value will be interpreted as.  int/uint/bool can be
    * reinterpreted trivially.  The most important cases are between float and
    * non-float.
    */
   if (alu->op != nir_op_mov && alu->op != nir_op_bcsel) {
      const nir_alu_type use_base_type =
         nir_alu_type_get_base_type(use_type);
      const nir_alu_type src_base_type =
         nir_alu_type_get_base_type(nir_op_infos[alu->op].output_type);

      if (use_base_type != src_base_type &&
          (use_base_type == nir_type_float ||
           src_base_type == nir_type_float)) {
         return (struct ssa_result_range){unknown, false};
      }
   }

   struct hash_entry *he = _mesa_hash_table_search(ht, pack_key(alu, use_type));
   if (he != NULL)
      return unpack_data(he->data);

   struct ssa_result_range r = {unknown, false};

   /* ge_zero: ge_zero + ge_zero
    *
    * gt_zero: gt_zero + eq_zero
    *        | gt_zero + ge_zero
    *        | eq_zero + gt_zero   # Addition is commutative
    *        | ge_zero + gt_zero   # Addition is commutative
    *        | gt_zero + gt_zero
    *        ;
    *
    * le_zero: le_zero + le_zero
    *
    * lt_zero: lt_zero + eq_zero
    *        | lt_zero + le_zero
    *        | eq_zero + lt_zero   # Addition is commutative
    *        | le_zero + lt_zero   # Addition is commutative
    *        | lt_zero + lt_zero
    *        ;
    *
    * ne_zero: eq_zero + ne_zero
    *        | ne_zero + eq_zero   # Addition is commutative
    *        ;
    *
    * eq_zero: eq_zero + eq_zero
    *        ;
    *
    * All other cases are 'unknown'.  The seeming odd entry is (ne_zero,
    * ne_zero), but that could be (-5, +5) which is not ne_zero.
    */
   static const enum ssa_ranges fadd_table[last_range + 1][last_range + 1] = {
      /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
      /* unknown */ { _______, _______, _______, _______, _______, _______, _______ },
      /* lt_zero */ { _______, lt_zero, lt_zero, _______, _______, _______, lt_zero },
      /* le_zero */ { _______, lt_zero, le_zero, _______, _______, _______, le_zero },
      /* gt_zero */ { _______, _______, _______, gt_zero, gt_zero, _______, gt_zero },
      /* ge_zero */ { _______, _______, _______, gt_zero, ge_zero, _______, ge_zero },
      /* ne_zero */ { _______, _______, _______, _______, _______, _______, ne_zero },
      /* eq_zero */ { _______, lt_zero, le_zero, gt_zero, ge_zero, ne_zero, eq_zero },
   };

   ASSERT_TABLE_IS_COMMUTATIVE(fadd_table);
   ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_2_SOURCE(fadd_table);
   ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_2_SOURCE(fadd_table);

   /* Due to flush-to-zero semanatics of floating-point numbers with very
    * small mangnitudes, we can never really be sure a result will be
    * non-zero.
    *
    * ge_zero: ge_zero * ge_zero
    *        | ge_zero * gt_zero
    *        | ge_zero * eq_zero
    *        | le_zero * lt_zero
    *        | lt_zero * le_zero  # Multiplication is commutative
    *        | le_zero * le_zero
    *        | gt_zero * ge_zero  # Multiplication is commutative
    *        | eq_zero * ge_zero  # Multiplication is commutative
    *        | a * a              # Left source == right source
    *        | gt_zero * gt_zero
    *        | lt_zero * lt_zero
    *        ;
    *
    * le_zero: ge_zero * le_zero
    *        | ge_zero * lt_zero
    *        | lt_zero * ge_zero  # Multiplication is commutative
    *        | le_zero * ge_zero  # Multiplication is commutative
    *        | le_zero * gt_zero
    *        | lt_zero * gt_zero
    *        | gt_zero * lt_zero  # Multiplication is commutative
    *        ;
    *
    * eq_zero: eq_zero * <any>
    *          <any> * eq_zero    # Multiplication is commutative
    *
    * All other cases are 'unknown'.
    */
   static const enum ssa_ranges fmul_table[last_range + 1][last_range + 1] = {
      /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
      /* unknown */ { _______, _______, _______, _______, _______, _______, eq_zero },
      /* lt_zero */ { _______, ge_zero, ge_zero, le_zero, le_zero, _______, eq_zero },
      /* le_zero */ { _______, ge_zero, ge_zero, le_zero, le_zero, _______, eq_zero },
      /* gt_zero */ { _______, le_zero, le_zero, ge_zero, ge_zero, _______, eq_zero },
      /* ge_zero */ { _______, le_zero, le_zero, ge_zero, ge_zero, _______, eq_zero },
      /* ne_zero */ { _______, _______, _______, _______, _______, _______, eq_zero },
      /* eq_zero */ { eq_zero, eq_zero, eq_zero, eq_zero, eq_zero, eq_zero, eq_zero }
   };

   ASSERT_TABLE_IS_COMMUTATIVE(fmul_table);
   ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_2_SOURCE(fmul_table);
   ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_2_SOURCE(fmul_table);

   static const enum ssa_ranges fneg_table[last_range + 1] = {
   /* unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
      _______, gt_zero, ge_zero, lt_zero, le_zero, ne_zero, eq_zero
   };

   ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_1_SOURCE(fneg_table);
   ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_1_SOURCE(fneg_table);


   switch (alu->op) {
   case nir_op_b2f32:
   case nir_op_b2i32:
      r = (struct ssa_result_range){ge_zero, alu->op == nir_op_b2f32};
      break;

   case nir_op_bcsel: {
      const struct ssa_result_range left =
         analyze_expression(alu, 1, ht, use_type);
      const struct ssa_result_range right =
         analyze_expression(alu, 2, ht, use_type);

      r.is_integral = left.is_integral && right.is_integral;

      /* le_zero: bcsel(<any>, le_zero, lt_zero)
       *        | bcsel(<any>, eq_zero, lt_zero)
       *        | bcsel(<any>, le_zero, eq_zero)
       *        | bcsel(<any>, lt_zero, le_zero)
       *        | bcsel(<any>, lt_zero, eq_zero)
       *        | bcsel(<any>, eq_zero, le_zero)
       *        | bcsel(<any>, le_zero, le_zero)
       *        ;
       *
       * lt_zero: bcsel(<any>, lt_zero, lt_zero)
       *        ;
       *
       * ge_zero: bcsel(<any>, ge_zero, ge_zero)
       *        | bcsel(<any>, ge_zero, gt_zero)
       *        | bcsel(<any>, ge_zero, eq_zero)
       *        | bcsel(<any>, gt_zero, ge_zero)
       *        | bcsel(<any>, eq_zero, ge_zero)
       *        ;
       *
       * gt_zero: bcsel(<any>, gt_zero, gt_zero)
       *        ;
       *
       * ne_zero: bcsel(<any>, ne_zero, gt_zero)
       *        | bcsel(<any>, ne_zero, lt_zero)
       *        | bcsel(<any>, gt_zero, lt_zero)
       *        | bcsel(<any>, gt_zero, ne_zero)
       *        | bcsel(<any>, lt_zero, ne_zero)
       *        | bcsel(<any>, lt_zero, gt_zero)
       *        | bcsel(<any>, ne_zero, ne_zero)
       *        ;
       *
       * eq_zero: bcsel(<any>, eq_zero, eq_zero)
       *        ;
       *
       * All other cases are 'unknown'.
       *
       * The ranges could be tightened if the range of the first source is
       * known.  However, opt_algebraic will (eventually) elminiate the bcsel
       * if the condition is known.
       */
      static const enum ssa_ranges table[last_range + 1][last_range + 1] = {
         /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
         /* unknown */ { _______, _______, _______, _______, _______, _______, _______ },
         /* lt_zero */ { _______, lt_zero, le_zero, ne_zero, _______, ne_zero, le_zero },
         /* le_zero */ { _______, le_zero, le_zero, _______, _______, _______, le_zero },
         /* gt_zero */ { _______, ne_zero, _______, gt_zero, ge_zero, ne_zero, ge_zero },
         /* ge_zero */ { _______, _______, _______, ge_zero, ge_zero, _______, ge_zero },
         /* ne_zero */ { _______, ne_zero, _______, ne_zero, _______, ne_zero, _______ },
         /* eq_zero */ { _______, le_zero, le_zero, ge_zero, ge_zero, _______, eq_zero },
      };

      ASSERT_TABLE_IS_COMMUTATIVE(table);
      ASSERT_TABLE_IS_DIAGONAL(table);
      ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_2_SOURCE(table);

      r.range = table[left.range][right.range];
      break;
   }

   case nir_op_i2f32:
   case nir_op_u2f32:
      r = analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      r.is_integral = true;

      if (r.range == unknown && alu->op == nir_op_u2f32)
         r.range = ge_zero;

      break;

   case nir_op_fabs:
      r = analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      switch (r.range) {
      case unknown:
      case le_zero:
      case ge_zero:
         r.range = ge_zero;
         break;

      case lt_zero:
      case gt_zero:
      case ne_zero:
         r.range = gt_zero;
         break;

      case eq_zero:
         break;
      }

      break;

   case nir_op_fadd: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range right =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));

      r.is_integral = left.is_integral && right.is_integral;
      r.range = fadd_table[left.range][right.range];
      break;
   }

   case nir_op_fexp2: {
      /* If the parameter might be less than zero, the mathematically result
       * will be on (0, 1).  For sufficiently large magnitude negative
       * parameters, the result will flush to zero.
       */
      static const enum ssa_ranges table[last_range + 1] = {
      /* unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
         ge_zero, ge_zero, ge_zero, gt_zero, gt_zero, ge_zero, gt_zero
      };

      r = analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_1_SOURCE(table);
      ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_1_SOURCE(table);

      r.is_integral = r.is_integral && is_not_negative(r.range);
      r.range = table[r.range];
      break;
   }

   case nir_op_fmax: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range right =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));

      r.is_integral = left.is_integral && right.is_integral;

      /* gt_zero: fmax(gt_zero, *)
       *        | fmax(*, gt_zero)        # Treat fmax as commutative
       *        ;
       *
       * ge_zero: fmax(ge_zero, ne_zero)
       *        | fmax(ge_zero, lt_zero)
       *        | fmax(ge_zero, le_zero)
       *        | fmax(ge_zero, eq_zero)
       *        | fmax(ne_zero, ge_zero)  # Treat fmax as commutative
       *        | fmax(lt_zero, ge_zero)  # Treat fmax as commutative
       *        | fmax(le_zero, ge_zero)  # Treat fmax as commutative
       *        | fmax(eq_zero, ge_zero)  # Treat fmax as commutative
       *        | fmax(ge_zero, ge_zero)
       *        ;
       *
       * le_zero: fmax(le_zero, lt_zero)
       *        | fmax(lt_zero, le_zero)  # Treat fmax as commutative
       *        | fmax(le_zero, le_zero)
       *        ;
       *
       * lt_zero: fmax(lt_zero, lt_zero)
       *        ;
       *
       * ne_zero: fmax(ne_zero, lt_zero)
       *        | fmax(lt_zero, ne_zero)  # Treat fmax as commutative
       *        | fmax(ne_zero, ne_zero)
       *        ;
       *
       * eq_zero: fmax(eq_zero, le_zero)
       *        | fmax(eq_zero, lt_zero)
       *        | fmax(le_zero, eq_zero)  # Treat fmax as commutative
       *        | fmax(lt_zero, eq_zero)  # Treat fmax as commutative
       *        | fmax(eq_zero, eq_zero)
       *        ;
       *
       * All other cases are 'unknown'.
       */
      static const enum ssa_ranges table[last_range + 1][last_range + 1] = {
         /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
         /* unknown */ { _______, _______, _______, gt_zero, ge_zero, _______, _______ },
         /* lt_zero */ { _______, lt_zero, le_zero, gt_zero, ge_zero, ne_zero, eq_zero },
         /* le_zero */ { _______, le_zero, le_zero, gt_zero, ge_zero, _______, eq_zero },
         /* gt_zero */ { gt_zero, gt_zero, gt_zero, gt_zero, gt_zero, gt_zero, gt_zero },
         /* ge_zero */ { ge_zero, ge_zero, ge_zero, gt_zero, ge_zero, ge_zero, ge_zero },
         /* ne_zero */ { _______, ne_zero, _______, gt_zero, ge_zero, ne_zero, _______ },
         /* eq_zero */ { _______, eq_zero, eq_zero, gt_zero, ge_zero, _______, eq_zero }
      };

      /* Treat fmax as commutative. */
      ASSERT_TABLE_IS_COMMUTATIVE(table);
      ASSERT_TABLE_IS_DIAGONAL(table);
      ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_2_SOURCE(table);

      r.range = table[left.range][right.range];
      break;
   }

   case nir_op_fmin: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range right =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));

      r.is_integral = left.is_integral && right.is_integral;

      /* lt_zero: fmin(lt_zero, *)
       *        | fmin(*, lt_zero)        # Treat fmin as commutative
       *        ;
       *
       * le_zero: fmin(le_zero, ne_zero)
       *        | fmin(le_zero, gt_zero)
       *        | fmin(le_zero, ge_zero)
       *        | fmin(le_zero, eq_zero)
       *        | fmin(ne_zero, le_zero)  # Treat fmin as commutative
       *        | fmin(gt_zero, le_zero)  # Treat fmin as commutative
       *        | fmin(ge_zero, le_zero)  # Treat fmin as commutative
       *        | fmin(eq_zero, le_zero)  # Treat fmin as commutative
       *        | fmin(le_zero, le_zero)
       *        ;
       *
       * ge_zero: fmin(ge_zero, gt_zero)
       *        | fmin(gt_zero, ge_zero)  # Treat fmin as commutative
       *        | fmin(ge_zero, ge_zero)
       *        ;
       *
       * gt_zero: fmin(gt_zero, gt_zero)
       *        ;
       *
       * ne_zero: fmin(ne_zero, gt_zero)
       *        | fmin(gt_zero, ne_zero)  # Treat fmin as commutative
       *        | fmin(ne_zero, ne_zero)
       *        ;
       *
       * eq_zero: fmin(eq_zero, ge_zero)
       *        | fmin(eq_zero, gt_zero)
       *        | fmin(ge_zero, eq_zero)  # Treat fmin as commutative
       *        | fmin(gt_zero, eq_zero)  # Treat fmin as commutative
       *        | fmin(eq_zero, eq_zero)
       *        ;
       *
       * All other cases are 'unknown'.
       */
      static const enum ssa_ranges table[last_range + 1][last_range + 1] = {
         /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
         /* unknown */ { _______, lt_zero, le_zero, _______, _______, _______, _______ },
         /* lt_zero */ { lt_zero, lt_zero, lt_zero, lt_zero, lt_zero, lt_zero, lt_zero },
         /* le_zero */ { le_zero, lt_zero, le_zero, le_zero, le_zero, le_zero, le_zero },
         /* gt_zero */ { _______, lt_zero, le_zero, gt_zero, ge_zero, ne_zero, eq_zero },
         /* ge_zero */ { _______, lt_zero, le_zero, ge_zero, ge_zero, _______, eq_zero },
         /* ne_zero */ { _______, lt_zero, le_zero, ne_zero, _______, ne_zero, _______ },
         /* eq_zero */ { _______, lt_zero, le_zero, eq_zero, eq_zero, _______, eq_zero }
      };

      /* Treat fmin as commutative. */
      ASSERT_TABLE_IS_COMMUTATIVE(table);
      ASSERT_TABLE_IS_DIAGONAL(table);
      ASSERT_UNION_OF_OTHERS_MATCHES_UNKNOWN_2_SOURCE(table);

      r.range = table[left.range][right.range];
      break;
   }

   case nir_op_fmul: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range right =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));

      r.is_integral = left.is_integral && right.is_integral;

      /* x * x => ge_zero */
      if (left.range != eq_zero && nir_alu_srcs_equal(alu, alu, 0, 1)) {
         /* Even if x > 0, the result of x*x can be zero when x is, for
          * example, a subnormal number.
          */
         r.range = ge_zero;
      } else if (left.range != eq_zero && nir_alu_srcs_negative_equal(alu, alu, 0, 1)) {
         /* -x * x => le_zero. */
         r.range = le_zero;
      } else
         r.range = fmul_table[left.range][right.range];

      break;
   }

   case nir_op_frcp:
      r = (struct ssa_result_range){
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0)).range,
         false
      };
      break;

   case nir_op_mov:
      r = analyze_expression(alu, 0, ht, use_type);
      break;

   case nir_op_fneg:
      r = analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      r.range = fneg_table[r.range];
      break;

   case nir_op_fsat:
      r = analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      switch (r.range) {
      case le_zero:
      case lt_zero:
         r.range = eq_zero;
         r.is_integral = true;
         break;

      case eq_zero:
         assert(r.is_integral);
      case gt_zero:
      case ge_zero:
         /* The fsat doesn't add any information in these cases. */
         break;

      case ne_zero:
      case unknown:
         /* Since the result must be in [0, 1], the value must be >= 0. */
         r.range = ge_zero;
         break;
      }
      break;

   case nir_op_fsign:
      r = (struct ssa_result_range){
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0)).range,
         true
      };
      break;

   case nir_op_fsqrt:
   case nir_op_frsq:
      r = (struct ssa_result_range){ge_zero, false};
      break;

   case nir_op_ffloor: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      r.is_integral = true;

      if (left.is_integral || left.range == le_zero || left.range == lt_zero)
         r.range = left.range;
      else if (left.range == ge_zero || left.range == gt_zero)
         r.range = ge_zero;
      else if (left.range == ne_zero)
         r.range = unknown;

      break;
   }

   case nir_op_fceil: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      r.is_integral = true;

      if (left.is_integral || left.range == ge_zero || left.range == gt_zero)
         r.range = left.range;
      else if (left.range == le_zero || left.range == lt_zero)
         r.range = le_zero;
      else if (left.range == ne_zero)
         r.range = unknown;

      break;
   }

   case nir_op_ftrunc: {
      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));

      r.is_integral = true;

      if (left.is_integral)
         r.range = left.range;
      else if (left.range == ge_zero || left.range == gt_zero)
         r.range = ge_zero;
      else if (left.range == le_zero || left.range == lt_zero)
         r.range = le_zero;
      else if (left.range == ne_zero)
         r.range = unknown;

      break;
   }

   case nir_op_flt:
   case nir_op_fge:
   case nir_op_feq:
   case nir_op_fne:
   case nir_op_ilt:
   case nir_op_ige:
   case nir_op_ieq:
   case nir_op_ine:
   case nir_op_ult:
   case nir_op_uge:
      /* Boolean results are 0 or -1. */
      r = (struct ssa_result_range){le_zero, false};
      break;

   case nir_op_fpow: {
      /* Due to flush-to-zero semanatics of floating-point numbers with very
       * small mangnitudes, we can never really be sure a result will be
       * non-zero.
       *
       * NIR uses pow() and powf() to constant evaluate nir_op_fpow.  The man
       * page for that function says:
       *
       *    If y is 0, the result is 1.0 (even if x is a NaN).
       *
       * gt_zero: pow(*, eq_zero)
       *        | pow(eq_zero, lt_zero)   # 0^-y = +inf
       *        | pow(eq_zero, le_zero)   # 0^-y = +inf or 0^0 = 1.0
       *        ;
       *
       * eq_zero: pow(eq_zero, gt_zero)
       *        ;
       *
       * ge_zero: pow(gt_zero, gt_zero)
       *        | pow(gt_zero, ge_zero)
       *        | pow(gt_zero, lt_zero)
       *        | pow(gt_zero, le_zero)
       *        | pow(gt_zero, ne_zero)
       *        | pow(gt_zero, unknown)
       *        | pow(ge_zero, gt_zero)
       *        | pow(ge_zero, ge_zero)
       *        | pow(ge_zero, lt_zero)
       *        | pow(ge_zero, le_zero)
       *        | pow(ge_zero, ne_zero)
       *        | pow(ge_zero, unknown)
       *        | pow(eq_zero, ge_zero)  # 0^0 = 1.0 or 0^+y = 0.0
       *        | pow(eq_zero, ne_zero)  # 0^-y = +inf or 0^+y = 0.0
       *        | pow(eq_zero, unknown)  # union of all other y cases
       *        ;
       *
       * All other cases are unknown.
       *
       * We could do better if the right operand is a constant, integral
       * value.
       */
      static const enum ssa_ranges table[last_range + 1][last_range + 1] = {
         /* left\right   unknown  lt_zero  le_zero  gt_zero  ge_zero  ne_zero  eq_zero */
         /* unknown */ { _______, _______, _______, _______, _______, _______, gt_zero },
         /* lt_zero */ { _______, _______, _______, _______, _______, _______, gt_zero },
         /* le_zero */ { _______, _______, _______, _______, _______, _______, gt_zero },
         /* gt_zero */ { ge_zero, ge_zero, ge_zero, ge_zero, ge_zero, ge_zero, gt_zero },
         /* ge_zero */ { ge_zero, ge_zero, ge_zero, ge_zero, ge_zero, ge_zero, gt_zero },
         /* ne_zero */ { _______, _______, _______, _______, _______, _______, gt_zero },
         /* eq_zero */ { ge_zero, gt_zero, gt_zero, eq_zero, ge_zero, ge_zero, gt_zero },
      };

      const struct ssa_result_range left =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range right =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));

      ASSERT_UNION_OF_DISJOINT_MATCHES_UNKNOWN_2_SOURCE(table);
      ASSERT_UNION_OF_EQ_AND_STRICT_INEQ_MATCHES_NONSTRICT_2_SOURCE(table);

      r.is_integral = left.is_integral && right.is_integral &&
                      is_not_negative(right.range);
      r.range = table[left.range][right.range];
      break;
   }

   case nir_op_ffma: {
      const struct ssa_result_range first =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range second =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));
      const struct ssa_result_range third =
         analyze_expression(alu, 2, ht, nir_alu_src_type(alu, 2));

      r.is_integral = first.is_integral && second.is_integral &&
                      third.is_integral;

      enum ssa_ranges fmul_range;

      if (first.range != eq_zero && nir_alu_srcs_equal(alu, alu, 0, 1)) {
         /* See handling of nir_op_fmul for explanation of why ge_zero is the
          * range.
          */
         fmul_range = ge_zero;
      } else if (first.range != eq_zero && nir_alu_srcs_negative_equal(alu, alu, 0, 1)) {
         /* -x * x => le_zero */
         fmul_range = le_zero;
      } else
         fmul_range = fmul_table[first.range][second.range];

      r.range = fadd_table[fmul_range][third.range];
      break;
   }

   case nir_op_flrp: {
      const struct ssa_result_range first =
         analyze_expression(alu, 0, ht, nir_alu_src_type(alu, 0));
      const struct ssa_result_range second =
         analyze_expression(alu, 1, ht, nir_alu_src_type(alu, 1));
      const struct ssa_result_range third =
         analyze_expression(alu, 2, ht, nir_alu_src_type(alu, 2));

      r.is_integral = first.is_integral && second.is_integral &&
                      third.is_integral;

      /* Decompose the flrp to first + third * (second + -first) */
      const enum ssa_ranges inner_fadd_range =
         fadd_table[second.range][fneg_table[first.range]];

      const enum ssa_ranges fmul_range =
         fmul_table[third.range][inner_fadd_range];

      r.range = fadd_table[first.range][fmul_range];
      break;
   }

   default:
      r = (struct ssa_result_range){unknown, false};
      break;
   }

   if (r.range == eq_zero)
      r.is_integral = true;

   _mesa_hash_table_insert(ht, pack_key(alu, use_type), pack_data(r));
   return r;
}

#undef _______

struct ssa_result_range
nir_analyze_range(struct hash_table *range_ht,
                  const nir_alu_instr *instr, unsigned src)
{
   return analyze_expression(instr, src, range_ht,
                             nir_alu_src_type(instr, src));
}
