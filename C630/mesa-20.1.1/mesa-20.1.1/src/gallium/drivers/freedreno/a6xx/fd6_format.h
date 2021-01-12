/*
 * Copyright (C) 2016 Rob Clark <robclark@freedesktop.org>
 * Copyright © 2018 Google, Inc.
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

#ifndef FD6_UTIL_H_
#define FD6_UTIL_H_

#include "freedreno_resource.h"
#include "freedreno_util.h"

#include "a6xx.xml.h"

enum a6xx_format fd6_pipe2vtx(enum pipe_format format);
enum a6xx_format fd6_pipe2tex(enum pipe_format format);
enum a6xx_format fd6_pipe2color(enum pipe_format format);
enum a3xx_color_swap fd6_pipe2swap(enum pipe_format format);
enum a6xx_tex_fetchsize fd6_pipe2fetchsize(enum pipe_format format);
enum a6xx_depth_format fd6_pipe2depth(enum pipe_format format);
enum a6xx_tex_swiz fd6_pipe2swiz(unsigned swiz);

void fd6_tex_swiz(enum pipe_format format, unsigned char *swiz,
			 unsigned swizzle_r, unsigned swizzle_g,
			 unsigned swizzle_b, unsigned swizzle_a);

uint32_t fd6_tex_const_0(struct pipe_resource *prsc,
					  unsigned level, enum pipe_format format,
					  unsigned swizzle_r, unsigned swizzle_g,
					  unsigned swizzle_b, unsigned swizzle_a);

static inline enum a6xx_2d_ifmt
fd6_ifmt(enum a6xx_format fmt)
{
	switch (fmt) {
	case FMT6_A8_UNORM:
	case FMT6_8_UNORM:
	case FMT6_8_SNORM:
	case FMT6_8_8_UNORM:
	case FMT6_8_8_SNORM:
	case FMT6_8_8_8_8_UNORM:
	case FMT6_8_8_8_X8_UNORM:
	case FMT6_8_8_8_8_SNORM:
		return R2D_UNORM8;

	case FMT6_32_UINT:
	case FMT6_32_SINT:
	case FMT6_32_32_UINT:
	case FMT6_32_32_SINT:
	case FMT6_32_32_32_32_UINT:
	case FMT6_32_32_32_32_SINT:
		return R2D_INT32;

	case FMT6_16_UINT:
	case FMT6_16_SINT:
	case FMT6_16_16_UINT:
	case FMT6_16_16_SINT:
	case FMT6_16_16_16_16_UINT:
	case FMT6_16_16_16_16_SINT:
		return R2D_INT16;

	case FMT6_8_UINT:
	case FMT6_8_SINT:
	case FMT6_8_8_UINT:
	case FMT6_8_8_SINT:
	case FMT6_8_8_8_8_UINT:
	case FMT6_8_8_8_8_SINT:
		return R2D_INT8;

	case FMT6_16_UNORM:
	case FMT6_16_SNORM:
	case FMT6_16_16_UNORM:
	case FMT6_16_16_SNORM:
	case FMT6_16_16_16_16_UNORM:
	case FMT6_16_16_16_16_SNORM:
	case FMT6_32_FLOAT:
	case FMT6_32_32_FLOAT:
	case FMT6_32_32_32_32_FLOAT:
		return R2D_FLOAT32;

	case FMT6_16_FLOAT:
	case FMT6_16_16_FLOAT:
	case FMT6_16_16_16_16_FLOAT:
	case FMT6_11_11_10_FLOAT:
		return R2D_FLOAT16;

	case FMT6_10_10_10_2_UNORM_DEST:
	case FMT6_4_4_4_4_UNORM:
	case FMT6_5_5_5_1_UNORM:
	case FMT6_5_6_5_UNORM:
	case FMT6_10_10_10_2_UINT:
	case FMT6_Z24_UNORM_S8_UINT:
	case FMT6_Z24_UNORM_S8_UINT_AS_R8G8B8A8:
		return R2D_RAW;
	default:
		unreachable("bad format");
		return 0;
	}
}

static inline uint32_t
fd6_resource_swap(struct fd_resource *rsc, enum pipe_format format)
{
	return rsc->layout.tile_mode ? WZYX : fd6_pipe2swap(format);
}

#endif /* FD6_UTIL_H_ */
