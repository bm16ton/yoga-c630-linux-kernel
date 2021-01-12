/*
 * Copyright (C) 2014 Rob Clark <robclark@freedesktop.org>
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

#ifndef IR3_SHADER_H_
#define IR3_SHADER_H_

#include <stdio.h>

#include "c11/threads.h"
#include "compiler/shader_enums.h"
#include "compiler/nir/nir.h"
#include "util/bitscan.h"

#include "ir3.h"

struct glsl_type;

/* driver param indices: */
enum ir3_driver_param {
	/* compute shader driver params: */
	IR3_DP_NUM_WORK_GROUPS_X = 0,
	IR3_DP_NUM_WORK_GROUPS_Y = 1,
	IR3_DP_NUM_WORK_GROUPS_Z = 2,
	IR3_DP_LOCAL_GROUP_SIZE_X = 4,
	IR3_DP_LOCAL_GROUP_SIZE_Y = 5,
	IR3_DP_LOCAL_GROUP_SIZE_Z = 6,
	/* NOTE: gl_NumWorkGroups should be vec4 aligned because
	 * glDispatchComputeIndirect() needs to load these from
	 * the info->indirect buffer.  Keep that in mind when/if
	 * adding any addition CS driver params.
	 */
	IR3_DP_CS_COUNT   = 8,   /* must be aligned to vec4 */

	/* vertex shader driver params: */
	IR3_DP_VTXID_BASE = 0,
	IR3_DP_VTXCNT_MAX = 1,
	IR3_DP_INSTID_BASE = 2,
	/* user-clip-plane components, up to 8x vec4's: */
	IR3_DP_UCP0_X     = 4,
	/* .... */
	IR3_DP_UCP7_W     = 35,
	IR3_DP_VS_COUNT   = 36   /* must be aligned to vec4 */
};

#define IR3_MAX_SHADER_BUFFERS   32
#define IR3_MAX_SHADER_IMAGES    32
#define IR3_MAX_SO_BUFFERS        4
#define IR3_MAX_SO_STREAMS        4
#define IR3_MAX_SO_OUTPUTS       64
#define IR3_MAX_UBO_PUSH_RANGES  32


/**
 * Describes the layout of shader consts.  This includes:
 *   + User consts + driver lowered UBO ranges
 *   + SSBO sizes
 *   + Image sizes/dimensions
 *   + Driver params (ie. IR3_DP_*)
 *   + TFBO addresses (for generations that do not have hardware streamout)
 *   + Lowered immediates
 *
 * For consts needed to pass internal values to shader which may or may not
 * be required, rather than allocating worst-case const space, we scan the
 * shader and allocate consts as-needed:
 *
 *   + SSBO sizes: only needed if shader has a get_buffer_size intrinsic
 *     for a given SSBO
 *
 *   + Image dimensions: needed to calculate pixel offset, but only for
 *     images that have a image_store intrinsic
 *
 * Layout of constant registers, each section aligned to vec4.  Note
 * that pointer size (ubo, etc) changes depending on generation.
 *
 *    user consts
 *    UBO addresses
 *    SSBO sizes
 *    if (vertex shader) {
 *        driver params (IR3_DP_*)
 *        if (stream_output.num_outputs > 0)
 *           stream-out addresses
 *    } else if (compute_shader) {
 *        driver params (IR3_DP_*)
 *    }
 *    immediates
 *
 * Immediates go last mostly because they are inserted in the CP pass
 * after the nir -> ir3 frontend.
 *
 * Note UBO size in bytes should be aligned to vec4
 */
struct ir3_const_state {
	unsigned num_ubos;
	unsigned num_reserved_user_consts;
	unsigned num_driver_params;   /* scalar */

	struct {
		/* user const start at zero */
		unsigned ubo;
		/* NOTE that a3xx might need a section for SSBO addresses too */
		unsigned ssbo_sizes;
		unsigned image_dims;
		unsigned driver_param;
		unsigned tfbo;
		unsigned primitive_param;
		unsigned primitive_map;
		unsigned immediate;
	} offsets;

	struct {
		uint32_t mask;  /* bitmask of SSBOs that have get_buffer_size */
		uint32_t count; /* number of consts allocated */
		/* one const allocated per SSBO which has get_buffer_size,
		 * ssbo_sizes.off[ssbo_id] is offset from start of ssbo_sizes
		 * consts:
		 */
		uint32_t off[IR3_MAX_SHADER_BUFFERS];
	} ssbo_size;

	struct {
		uint32_t mask;  /* bitmask of images that have image_store */
		uint32_t count; /* number of consts allocated */
		/* three const allocated per image which has image_store:
		 *  + cpp         (bytes per pixel)
		 *  + pitch       (y pitch)
		 *  + array_pitch (z pitch)
		 */
		uint32_t off[IR3_MAX_SHADER_IMAGES];
	} image_dims;

	unsigned immediate_idx;
	unsigned immediates_count;
	unsigned immediates_size;
	struct {
		uint32_t val[4];
	} *immediates;
};

/**
 * A single output for vertex transform feedback.
 */
struct ir3_stream_output {
	unsigned register_index:6;  /**< 0 to 63 (OUT index) */
	unsigned start_component:2; /** 0 to 3 */
	unsigned num_components:3;  /** 1 to 4 */
	unsigned output_buffer:3;   /**< 0 to PIPE_MAX_SO_BUFFERS */
	unsigned dst_offset:16;     /**< offset into the buffer in dwords */
	unsigned stream:2;          /**< 0 to 3 */
};

/**
 * Stream output for vertex transform feedback.
 */
struct ir3_stream_output_info {
	unsigned num_outputs;
	/** stride for an entire vertex for each buffer in dwords */
	uint16_t stride[IR3_MAX_SO_BUFFERS];

	/**
	 * Array of stream outputs, in the order they are to be written in.
	 * Selected components are tightly packed into the output buffer.
	 */
	struct ir3_stream_output output[IR3_MAX_SO_OUTPUTS];
};


/**
 * Starting from a4xx, HW supports pre-dispatching texture sampling
 * instructions prior to scheduling a shader stage, when the
 * coordinate maps exactly to an output of the previous stage.
 */

/**
 * There is a limit in the number of pre-dispatches allowed for any
 * given stage.
 */
#define IR3_MAX_SAMPLER_PREFETCH 4

/**
 * This is the output stream value for 'cmd', as used by blob. It may
 * encode the return type (in 3 bits) but it hasn't been verified yet.
 */
#define IR3_SAMPLER_PREFETCH_CMD 0x4
#define IR3_SAMPLER_BINDLESS_PREFETCH_CMD 0x6

/**
 * Stream output for texture sampling pre-dispatches.
 */
struct ir3_sampler_prefetch {
	uint8_t src;
	uint8_t samp_id;
	uint8_t tex_id;
	uint16_t samp_bindless_id;
	uint16_t tex_bindless_id;
	uint8_t dst;
	uint8_t wrmask;
	uint8_t half_precision;
	uint8_t cmd;
};


/* Configuration key used to identify a shader variant.. different
 * shader variants can be used to implement features not supported
 * in hw (two sided color), binning-pass vertex shader, etc.
 */
struct ir3_shader_key {
	union {
		struct {
			/*
			 * Combined Vertex/Fragment shader parameters:
			 */
			unsigned ucp_enables : 8;

			/* do we need to check {v,f}saturate_{s,t,r}? */
			unsigned has_per_samp : 1;

			/*
			 * Vertex shader variant parameters:
			 */
			unsigned vclamp_color : 1;

			/*
			 * Fragment shader variant parameters:
			 */
			unsigned sample_shading : 1;
			unsigned msaa           : 1;
			unsigned color_two_side : 1;
			unsigned half_precision : 1;
			/* used when shader needs to handle flat varyings (a4xx)
			 * for front/back color inputs to frag shader:
			 */
			unsigned rasterflat : 1;
			unsigned fclamp_color : 1;

			/* Indicates that this is a tessellation pipeline which requires a
			 * whole different kind of vertex shader.  In case of
			 * tessellation, this field also tells us which kind of output
			 * topology the TES uses, which the TCS needs to know.
			 */
#define IR3_TESS_NONE		0
#define IR3_TESS_TRIANGLES	1
#define IR3_TESS_QUADS		2
#define IR3_TESS_ISOLINES	3
			unsigned tessellation : 2;

			unsigned has_gs : 1;
		};
		uint32_t global;
	};

	/* bitmask of sampler which needs coords clamped for vertex
	 * shader:
	 */
	uint16_t vsaturate_s, vsaturate_t, vsaturate_r;

	/* bitmask of sampler which needs coords clamped for frag
	 * shader:
	 */
	uint16_t fsaturate_s, fsaturate_t, fsaturate_r;

	/* bitmask of ms shifts */
	uint32_t vsamples, fsamples;

	/* bitmask of samplers which need astc srgb workaround: */
	uint16_t vastc_srgb, fastc_srgb;
};

static inline bool
ir3_shader_key_equal(struct ir3_shader_key *a, struct ir3_shader_key *b)
{
	/* slow-path if we need to check {v,f}saturate_{s,t,r} */
	if (a->has_per_samp || b->has_per_samp)
		return memcmp(a, b, sizeof(struct ir3_shader_key)) == 0;
	return a->global == b->global;
}

/* will the two keys produce different lowering for a fragment shader? */
static inline bool
ir3_shader_key_changes_fs(struct ir3_shader_key *key, struct ir3_shader_key *last_key)
{
	if (last_key->has_per_samp || key->has_per_samp) {
		if ((last_key->fsaturate_s != key->fsaturate_s) ||
				(last_key->fsaturate_t != key->fsaturate_t) ||
				(last_key->fsaturate_r != key->fsaturate_r) ||
				(last_key->fsamples != key->fsamples) ||
				(last_key->fastc_srgb != key->fastc_srgb))
			return true;
	}

	if (last_key->fclamp_color != key->fclamp_color)
		return true;

	if (last_key->color_two_side != key->color_two_side)
		return true;

	if (last_key->half_precision != key->half_precision)
		return true;

	if (last_key->rasterflat != key->rasterflat)
		return true;

	if (last_key->ucp_enables != key->ucp_enables)
		return true;

	return false;
}

/* will the two keys produce different lowering for a vertex shader? */
static inline bool
ir3_shader_key_changes_vs(struct ir3_shader_key *key, struct ir3_shader_key *last_key)
{
	if (last_key->has_per_samp || key->has_per_samp) {
		if ((last_key->vsaturate_s != key->vsaturate_s) ||
				(last_key->vsaturate_t != key->vsaturate_t) ||
				(last_key->vsaturate_r != key->vsaturate_r) ||
				(last_key->vsamples != key->vsamples) ||
				(last_key->vastc_srgb != key->vastc_srgb))
			return true;
	}

	if (last_key->vclamp_color != key->vclamp_color)
		return true;

	if (last_key->ucp_enables != key->ucp_enables)
		return true;

	return false;
}

/* clears shader-key flags which don't apply to the given shader
 * stage
 */
static inline void
ir3_normalize_key(struct ir3_shader_key *key, gl_shader_stage type)
{
	switch (type) {
	case MESA_SHADER_FRAGMENT:
		if (key->has_per_samp) {
			key->vsaturate_s = 0;
			key->vsaturate_t = 0;
			key->vsaturate_r = 0;
			key->vastc_srgb = 0;
			key->vsamples = 0;
			key->has_gs = false; /* FS doesn't care */
			key->tessellation = IR3_TESS_NONE;
		}
		break;
	case MESA_SHADER_VERTEX:
	case MESA_SHADER_GEOMETRY:
		key->color_two_side = false;
		key->half_precision = false;
		key->rasterflat = false;
		if (key->has_per_samp) {
			key->fsaturate_s = 0;
			key->fsaturate_t = 0;
			key->fsaturate_r = 0;
			key->fastc_srgb = 0;
			key->fsamples = 0;
		}

		/* VS and GS only care about whether or not we're tessellating. */
		key->tessellation = !!key->tessellation;
		break;
	case MESA_SHADER_TESS_CTRL:
	case MESA_SHADER_TESS_EVAL:
		key->color_two_side = false;
		key->half_precision = false;
		key->rasterflat = false;
		if (key->has_per_samp) {
			key->fsaturate_s = 0;
			key->fsaturate_t = 0;
			key->fsaturate_r = 0;
			key->fastc_srgb = 0;
			key->fsamples = 0;
			key->vsaturate_s = 0;
			key->vsaturate_t = 0;
			key->vsaturate_r = 0;
			key->vastc_srgb = 0;
			key->vsamples = 0;
 		}
		break;
	default:
		/* TODO */
		break;
	}
}

/**
 * On a4xx+a5xx, Images share state with textures and SSBOs:
 *
 *   + Uses texture (cat5) state/instruction (isam) to read
 *   + Uses SSBO state and instructions (cat6) to write and for atomics
 *
 * Starting with a6xx, Images and SSBOs are basically the same thing,
 * with texture state and isam also used for SSBO reads.
 *
 * On top of that, gallium makes the SSBO (shader_buffers) state semi
 * sparse, with the first half of the state space used for atomic
 * counters lowered to atomic buffers.  We could ignore this, but I
 * don't think we could *really* handle the case of a single shader
 * that used the max # of textures + images + SSBOs.  And once we are
 * offsetting images by num_ssbos (or visa versa) to map them into
 * the same hardware state, the hardware state has become coupled to
 * the shader state, so at this point we might as well just use a
 * mapping table to remap things from image/SSBO idx to hw idx.
 *
 * To make things less (more?) confusing, for the hw "SSBO" state
 * (since it is really both SSBO and Image) I'll use the name "IBO"
 */
struct ir3_ibo_mapping {
#define IBO_INVALID 0xff
	/* Maps logical SSBO state to hw tex state: */
	uint8_t ssbo_to_tex[IR3_MAX_SHADER_BUFFERS];

	/* Maps logical Image state to hw tex state: */
	uint8_t image_to_tex[IR3_MAX_SHADER_IMAGES];

	/* Maps hw state back to logical SSBO or Image state:
	 *
	 * note IBO_SSBO ORd into values to indicate that the
	 * hw slot is used for SSBO state vs Image state.
	 */
#define IBO_SSBO    0x80
	uint8_t tex_to_image[32];

	uint8_t num_tex;    /* including real textures */
	uint8_t tex_base;   /* the number of real textures, ie. image/ssbo start here */
};

/* Represents half register in regid */
#define HALF_REG_ID    0x100

struct ir3_shader_variant {
	struct fd_bo *bo;

	/* variant id (for debug) */
	uint32_t id;

	struct ir3_shader_key key;

	/* vertex shaders can have an extra version for hwbinning pass,
	 * which is pointed to by so->binning:
	 */
	bool binning_pass;
//	union {
		struct ir3_shader_variant *binning;
		struct ir3_shader_variant *nonbinning;
//	};

	struct ir3_info info;
	struct ir3 *ir;

	/* Levels of nesting of flow control:
	 */
	unsigned branchstack;

	unsigned max_sun;
	unsigned loops;

	/* the instructions length is in units of instruction groups
	 * (4 instructions for a3xx, 16 instructions for a4xx.. each
	 * instruction is 2 dwords):
	 */
	unsigned instrlen;

	/* the constants length is in units of vec4's, and is the sum of
	 * the uniforms and the built-in compiler constants
	 */
	unsigned constlen;

	/* About Linkage:
	 *   + Let the frag shader determine the position/compmask for the
	 *     varyings, since it is the place where we know if the varying
	 *     is actually used, and if so, which components are used.  So
	 *     what the hw calls "outloc" is taken from the "inloc" of the
	 *     frag shader.
	 *   + From the vert shader, we only need the output regid
	 */

	bool frag_coord, frag_face, color0_mrt;

	/* NOTE: for input/outputs, slot is:
	 *   gl_vert_attrib  - for VS inputs
	 *   gl_varying_slot - for VS output / FS input
	 *   gl_frag_result  - for FS output
	 */

	/* varyings/outputs: */
	unsigned outputs_count;
	struct {
		uint8_t slot;
		uint8_t regid;
		bool    half : 1;
	} outputs[32 + 2];  /* +POSITION +PSIZE */
	bool writes_pos, writes_smask, writes_psize;

	/* attributes (VS) / varyings (FS):
	 * Note that sysval's should come *after* normal inputs.
	 */
	unsigned inputs_count;
	struct {
		uint8_t slot;
		uint8_t regid;
		uint8_t compmask;
		/* location of input (ie. offset passed to bary.f, etc).  This
		 * matches the SP_VS_VPC_DST_REG.OUTLOCn value (a3xx and a4xx
		 * have the OUTLOCn value offset by 8, presumably to account
		 * for gl_Position/gl_PointSize)
		 */
		uint8_t inloc;
		/* vertex shader specific: */
		bool    sysval     : 1;   /* slot is a gl_system_value */
		/* fragment shader specific: */
		bool    bary       : 1;   /* fetched varying (vs one loaded into reg) */
		bool    rasterflat : 1;   /* special handling for emit->rasterflat */
		bool    use_ldlv   : 1;   /* internal to ir3_compiler_nir */
		bool    half       : 1;
		enum glsl_interp_mode interpolate;
	} inputs[32 + 2];  /* +POSITION +FACE */

	/* sum of input components (scalar).  For frag shaders, it only counts
	 * the varying inputs:
	 */
	unsigned total_in;

	/* For frag shaders, the total number of inputs (not scalar,
	 * ie. SP_VS_PARAM_REG.TOTALVSOUTVAR)
	 */
	unsigned varying_in;

	/* Remapping table to map Image and SSBO to hw state: */
	struct ir3_ibo_mapping image_mapping;

	/* number of samplers/textures (which are currently 1:1): */
	int num_samp;

	/* is there an implicit sampler to read framebuffer (FS only).. if
	 * so the sampler-idx is 'num_samp - 1' (ie. it is appended after
	 * the last "real" texture)
	 */
	bool fb_read;

	/* do we have one or more SSBO instructions: */
	bool has_ssbo;

	/* Which bindless resources are used, for filling out sp_xs_config */
	bool bindless_tex;
	bool bindless_samp;
	bool bindless_ibo;
	bool bindless_ubo;

	/* do we need derivatives: */
	bool need_pixlod;

	bool need_fine_derivatives;

	/* do we have kill, image write, etc (which prevents early-z): */
	bool no_earlyz;

	bool per_samp;

	/* for astc srgb workaround, the number/base of additional
	 * alpha tex states we need, and index of original tex states
	 */
	struct {
		unsigned base, count;
		unsigned orig_idx[16];
	} astc_srgb;

	/* shader variants form a linked list: */
	struct ir3_shader_variant *next;

	/* replicated here to avoid passing extra ptrs everywhere: */
	gl_shader_stage type;
	struct ir3_shader *shader;

	/* texture sampler pre-dispatches */
	uint32_t num_sampler_prefetch;
	struct ir3_sampler_prefetch sampler_prefetch[IR3_MAX_SAMPLER_PREFETCH];
};

static inline const char *
ir3_shader_stage(struct ir3_shader_variant *v)
{
	switch (v->type) {
	case MESA_SHADER_VERTEX:     return v->binning_pass ? "BVERT" : "VERT";
	case MESA_SHADER_TESS_CTRL:  return "TCS";
	case MESA_SHADER_TESS_EVAL:  return "TES";
	case MESA_SHADER_GEOMETRY:   return "GEOM";
	case MESA_SHADER_FRAGMENT:   return "FRAG";
	case MESA_SHADER_COMPUTE:    return "CL";
	default:
		unreachable("invalid type");
		return NULL;
	}
}

struct ir3_ubo_range {
	uint32_t offset; /* start offset to push in the const register file */
	uint32_t block; /* Which constant block */
	uint32_t start, end; /* range of block that's actually used */
	uint16_t bindless_base; /* For bindless, which base register is used */
	bool bindless;
};

struct ir3_ubo_analysis_state {
	struct ir3_ubo_range range[IR3_MAX_UBO_PUSH_RANGES];
	uint32_t num_enabled;
	uint32_t size;
	uint32_t lower_count;
	uint32_t cmdstream_size; /* for per-gen backend to stash required cmdstream size */
};


struct ir3_shader {
	gl_shader_stage type;

	/* shader id (for debug): */
	uint32_t id;
	uint32_t variant_count;

	struct ir3_compiler *compiler;

	struct ir3_ubo_analysis_state ubo_state;
	struct ir3_const_state const_state;

	struct nir_shader *nir;
	struct ir3_stream_output_info stream_output;

	struct ir3_shader_variant *variants;
	mtx_t variants_lock;

	uint32_t output_size; /* Size in dwords of all outputs for VS, size of entire patch for HS. */

	/* Map from driver_location to byte offset in per-primitive storage */
	unsigned output_loc[32];
};

void * ir3_shader_assemble(struct ir3_shader_variant *v, uint32_t gpu_id);
struct ir3_shader_variant * ir3_shader_get_variant(struct ir3_shader *shader,
		struct ir3_shader_key *key, bool binning_pass, bool *created);
struct ir3_shader * ir3_shader_from_nir(struct ir3_compiler *compiler, nir_shader *nir);
void ir3_shader_destroy(struct ir3_shader *shader);
void ir3_shader_disasm(struct ir3_shader_variant *so, uint32_t *bin, FILE *out);
uint64_t ir3_shader_outputs(const struct ir3_shader *so);

int
ir3_glsl_type_size(const struct glsl_type *type, bool bindless);

/*
 * Helper/util:
 */

static inline int
ir3_find_output(const struct ir3_shader_variant *so, gl_varying_slot slot)
{
	int j;

	for (j = 0; j < so->outputs_count; j++)
		if (so->outputs[j].slot == slot)
			return j;

	/* it seems optional to have a OUT.BCOLOR[n] for each OUT.COLOR[n]
	 * in the vertex shader.. but the fragment shader doesn't know this
	 * so  it will always have both IN.COLOR[n] and IN.BCOLOR[n].  So
	 * at link time if there is no matching OUT.BCOLOR[n], we must map
	 * OUT.COLOR[n] to IN.BCOLOR[n].  And visa versa if there is only
	 * a OUT.BCOLOR[n] but no matching OUT.COLOR[n]
	 */
	if (slot == VARYING_SLOT_BFC0) {
		slot = VARYING_SLOT_COL0;
	} else if (slot == VARYING_SLOT_BFC1) {
		slot = VARYING_SLOT_COL1;
	} else if (slot == VARYING_SLOT_COL0) {
		slot = VARYING_SLOT_BFC0;
	} else if (slot == VARYING_SLOT_COL1) {
		slot = VARYING_SLOT_BFC1;
	} else {
		return -1;
	}

	for (j = 0; j < so->outputs_count; j++)
		if (so->outputs[j].slot == slot)
			return j;

	debug_assert(0);

	return -1;
}

static inline int
ir3_next_varying(const struct ir3_shader_variant *so, int i)
{
	while (++i < so->inputs_count)
		if (so->inputs[i].compmask && so->inputs[i].bary)
			break;
	return i;
}

struct ir3_shader_linkage {
	/* Maximum location either consumed by the fragment shader or produced by
	 * the last geometry stage, i.e. the size required for each vertex in the
	 * VPC in DWORD's.
	 */
	uint8_t max_loc;

	/* Number of entries in var. */
	uint8_t cnt;

	/* Bitset of locations used, including ones which are only used by the FS.
	 */
	uint32_t varmask[4];

	/* Map from VS output to location. */
	struct {
		uint8_t regid;
		uint8_t compmask;
		uint8_t loc;
	} var[32];

	/* location for fixed-function gl_PrimitiveID passthrough */
	uint8_t primid_loc;
};

static inline void
ir3_link_add(struct ir3_shader_linkage *l, uint8_t regid_, uint8_t compmask, uint8_t loc)
{


	for (int j = 0; j < util_last_bit(compmask); j++) {
		uint8_t comploc = loc + j;
		l->varmask[comploc / 32] |= 1 << (comploc % 32);
	}

	l->max_loc = MAX2(l->max_loc, loc + util_last_bit(compmask));

	if (regid_ != regid(63, 0)) {
		int i = l->cnt++;
		debug_assert(i < ARRAY_SIZE(l->var));

		l->var[i].regid    = regid_;
		l->var[i].compmask = compmask;
		l->var[i].loc      = loc;
	}
}

static inline void
ir3_link_shaders(struct ir3_shader_linkage *l,
		const struct ir3_shader_variant *vs,
		const struct ir3_shader_variant *fs,
		bool pack_vs_out)
{
	/* On older platforms, varmask isn't programmed at all, and it appears
	 * that the hardware generates a mask of used VPC locations using the VS
	 * output map, and hangs if a FS bary instruction references a location
	 * not in the list. This means that we need to have a dummy entry in the
	 * VS out map for things like gl_PointCoord which aren't written by the
	 * VS. Furthermore we can't use r63.x, so just pick a random register to
	 * use if there is no VS output.
	 */
	const unsigned default_regid = pack_vs_out ? regid(63, 0) : regid(0, 0);
	int j = -1, k;

	l->primid_loc = 0xff;

	while (l->cnt < ARRAY_SIZE(l->var)) {
		j = ir3_next_varying(fs, j);

		if (j >= fs->inputs_count)
			break;

		if (fs->inputs[j].inloc >= fs->total_in)
			continue;

		k = ir3_find_output(vs, fs->inputs[j].slot);

		if (k < 0 && fs->inputs[j].slot == VARYING_SLOT_PRIMITIVE_ID) {
			l->primid_loc = fs->inputs[j].inloc;
		}

		ir3_link_add(l, k >= 0 ? vs->outputs[k].regid : default_regid,
			fs->inputs[j].compmask, fs->inputs[j].inloc);
	}
}

static inline uint32_t
ir3_find_output_regid(const struct ir3_shader_variant *so, unsigned slot)
{
	int j;
	for (j = 0; j < so->outputs_count; j++)
		if (so->outputs[j].slot == slot) {
			uint32_t regid = so->outputs[j].regid;
			if (so->outputs[j].half)
				regid |= HALF_REG_ID;
			return regid;
		}
	return regid(63, 0);
}

#define VARYING_SLOT_GS_HEADER_IR3			(VARYING_SLOT_MAX + 0)
#define VARYING_SLOT_GS_VERTEX_FLAGS_IR3	(VARYING_SLOT_MAX + 1)
#define VARYING_SLOT_TCS_HEADER_IR3			(VARYING_SLOT_MAX + 2)


static inline uint32_t
ir3_find_sysval_regid(const struct ir3_shader_variant *so, unsigned slot)
{
	int j;
	for (j = 0; j < so->inputs_count; j++)
		if (so->inputs[j].sysval && (so->inputs[j].slot == slot))
			return so->inputs[j].regid;
	return regid(63, 0);
}

/* calculate register footprint in terms of half-regs (ie. one full
 * reg counts as two half-regs).
 */
static inline uint32_t
ir3_shader_halfregs(const struct ir3_shader_variant *v)
{
	return (2 * (v->info.max_reg + 1)) + (v->info.max_half_reg + 1);
}

static inline uint32_t
ir3_shader_nibo(const struct ir3_shader_variant *v)
{
	/* The dummy variant used in binning mode won't have an actual shader. */
	if (!v->shader)
		return 0;

	return v->shader->nir->info.num_ssbos + v->shader->nir->info.num_images;
}

#endif /* IR3_SHADER_H_ */
