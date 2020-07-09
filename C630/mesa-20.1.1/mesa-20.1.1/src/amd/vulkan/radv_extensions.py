COPYRIGHT = """\
/*
 * Copyright 2017 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
"""

import argparse
import copy
import re
import xml.etree.cElementTree as et

from mako.template import Template

def _bool_to_c_expr(b):
    if b is True:
        return 'true'
    if b is False:
        return 'false'
    return b

class Extension:
    def __init__(self, name, ext_version, enable):
        self.name = name
        self.ext_version = int(ext_version)
        if enable is True:
            self.enable = 'true';
        elif enable is False:
            self.enable = 'false';
        else:
            self.enable = enable;

class ApiVersion:
    def __init__(self, version, enable):
        self.version = version
        self.enable = _bool_to_c_expr(enable)

# Supported API versions.  Each one is the maximum patch version for the given
# version.  Version come in increasing order and each version is available if
# it's provided "enable" condition is true and all previous versions are
# available.
# TODO: The patch version should be unified!
API_VERSIONS = [
    ApiVersion('1.0.68',  True),
    ApiVersion('1.1.107', True),
    ApiVersion('1.2.131', '!ANDROID'),
]

MAX_API_VERSION = None # Computed later

# On Android, we disable all surface and swapchain extensions. Android's Vulkan
# loader implements VK_KHR_surface and VK_KHR_swapchain, and applications
# cannot access the driver's implementation. Moreoever, if the driver exposes
# the those extension strings, then tests dEQP-VK.api.info.instance.extensions
# and dEQP-VK.api.info.device fail due to the duplicated strings.
EXTENSIONS = [
    Extension('VK_ANDROID_external_memory_android_hardware_buffer', 3, 'RADV_SUPPORT_ANDROID_HARDWARE_BUFFER  && device->rad_info.has_syncobj_wait_for_submit'),
    Extension('VK_ANDROID_native_buffer',                 5, 'ANDROID && device->rad_info.has_syncobj_wait_for_submit'),
    Extension('VK_KHR_16bit_storage',                     1, '!device->use_aco || device->rad_info.chip_class >= GFX8'),
    Extension('VK_KHR_bind_memory2',                      1, True),
    Extension('VK_KHR_buffer_device_address',             1, True),
    Extension('VK_KHR_create_renderpass2',                1, True),
    Extension('VK_KHR_dedicated_allocation',              1, True),
    Extension('VK_KHR_depth_stencil_resolve',             1, True),
    Extension('VK_KHR_descriptor_update_template',        1, True),
    Extension('VK_KHR_device_group',                      1, True),
    Extension('VK_KHR_device_group_creation',             1, True),
    Extension('VK_KHR_draw_indirect_count',               1, True),
    Extension('VK_KHR_driver_properties',                 1, True),
    Extension('VK_KHR_external_fence',                    1, 'device->rad_info.has_syncobj_wait_for_submit'),
    Extension('VK_KHR_external_fence_capabilities',       1, True),
    Extension('VK_KHR_external_fence_fd',                 1, 'device->rad_info.has_syncobj_wait_for_submit'),
    Extension('VK_KHR_external_memory',                   1, True),
    Extension('VK_KHR_external_memory_capabilities',      1, True),
    Extension('VK_KHR_external_memory_fd',                1, True),
    Extension('VK_KHR_external_semaphore',                1, 'device->rad_info.has_syncobj'),
    Extension('VK_KHR_external_semaphore_capabilities',   1, True),
    Extension('VK_KHR_external_semaphore_fd',             1, 'device->rad_info.has_syncobj'),
    Extension('VK_KHR_get_display_properties2',           1, 'VK_USE_PLATFORM_DISPLAY_KHR'),
    Extension('VK_KHR_get_memory_requirements2',          1, True),
    Extension('VK_KHR_get_physical_device_properties2',   1, True),
    Extension('VK_KHR_get_surface_capabilities2',         1, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_image_format_list',                 1, True),
    Extension('VK_KHR_imageless_framebuffer',             1, True),
    Extension('VK_KHR_incremental_present',               1, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_maintenance1',                      1, True),
    Extension('VK_KHR_maintenance2',                      1, True),
    Extension('VK_KHR_maintenance3',                      1, True),
    Extension('VK_KHR_pipeline_executable_properties',    1, True),
    Extension('VK_KHR_push_descriptor',                   1, True),
    Extension('VK_KHR_relaxed_block_layout',              1, True),
    Extension('VK_KHR_sampler_mirror_clamp_to_edge',      1, True),
    Extension('VK_KHR_sampler_ycbcr_conversion',          1, True),
    Extension('VK_KHR_separate_depth_stencil_layouts',    1, True),
    Extension('VK_KHR_shader_atomic_int64',               1, 'LLVM_VERSION_MAJOR >= 9'),
    Extension('VK_KHR_shader_clock',                      1, True),
    Extension('VK_KHR_shader_draw_parameters',            1, True),
    Extension('VK_KHR_shader_float_controls',             1, True),
    Extension('VK_KHR_shader_float16_int8',               1, '!device->use_aco || device->rad_info.chip_class >= GFX8'),
    Extension('VK_KHR_shader_non_semantic_info',          1, True),
    Extension('VK_KHR_shader_subgroup_extended_types',    1, '!device->use_aco'),
    Extension('VK_KHR_spirv_1_4',                         1, True),
    Extension('VK_KHR_storage_buffer_storage_class',      1, True),
    Extension('VK_KHR_surface',                          25, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_surface_protected_capabilities',    1, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_swapchain',                        68, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_swapchain_mutable_format',          1, 'RADV_HAS_SURFACE'),
    Extension('VK_KHR_timeline_semaphore',                2, 'device->rad_info.has_syncobj_wait_for_submit'),
    Extension('VK_KHR_uniform_buffer_standard_layout',    1, True),
    Extension('VK_KHR_variable_pointers',                 1, True),
    Extension('VK_KHR_wayland_surface',                   6, 'VK_USE_PLATFORM_WAYLAND_KHR'),
    Extension('VK_KHR_xcb_surface',                       6, 'VK_USE_PLATFORM_XCB_KHR'),
    Extension('VK_KHR_xlib_surface',                      6, 'VK_USE_PLATFORM_XLIB_KHR'),
    Extension('VK_KHR_multiview',                         1, True),
    Extension('VK_KHR_display',                          23, 'VK_USE_PLATFORM_DISPLAY_KHR'),
    Extension('VK_KHR_8bit_storage',                      1, '!device->use_aco || device->rad_info.chip_class >= GFX8'),
    Extension('VK_EXT_direct_mode_display',               1, 'VK_USE_PLATFORM_DISPLAY_KHR'),
    Extension('VK_EXT_acquire_xlib_display',              1, 'VK_USE_PLATFORM_XLIB_XRANDR_EXT'),
    Extension('VK_EXT_buffer_device_address',             1, True),
    Extension('VK_EXT_calibrated_timestamps',             1, True),
    Extension('VK_EXT_conditional_rendering',             1, True),
    Extension('VK_EXT_conservative_rasterization',        1, 'device->rad_info.chip_class >= GFX9'),
    Extension('VK_EXT_display_surface_counter',           1, 'VK_USE_PLATFORM_DISPLAY_KHR'),
    Extension('VK_EXT_display_control',                   1, 'VK_USE_PLATFORM_DISPLAY_KHR'),
    Extension('VK_EXT_debug_report',                      9, True),
    Extension('VK_EXT_depth_clip_enable',                 1, True),
    Extension('VK_EXT_depth_range_unrestricted',          1, True),
    Extension('VK_EXT_descriptor_indexing',               2, True),
    Extension('VK_EXT_discard_rectangles',                1, True),
    Extension('VK_EXT_external_memory_dma_buf',           1, True),
    Extension('VK_EXT_external_memory_host',              1, 'device->rad_info.has_userptr'),
    Extension('VK_EXT_global_priority',                   1, 'device->rad_info.has_ctx_priority'),
    Extension('VK_EXT_host_query_reset',                  1, True),
    Extension('VK_EXT_index_type_uint8',                  1, 'device->rad_info.chip_class >= GFX8'),
    Extension('VK_EXT_inline_uniform_block',              1, True),
    # Disable line rasterization on GFX9 until the CTS failures have been resolved.
    Extension('VK_EXT_line_rasterization',                1, 'device->rad_info.chip_class != GFX9'),
    Extension('VK_EXT_memory_budget',                     1, True),
    Extension('VK_EXT_memory_priority',                   1, True),
    Extension('VK_EXT_pci_bus_info',                      2, True),
    Extension('VK_EXT_pipeline_creation_feedback',        1, True),
    Extension('VK_EXT_post_depth_coverage',               1, 'device->rad_info.chip_class >= GFX10'),
    Extension('VK_EXT_queue_family_foreign',              1, True),
    Extension('VK_EXT_robustness2',                       1, True),
    # Disable sample locations on GFX10 until the CTS failures have been resolved.
    Extension('VK_EXT_sample_locations',                  1, 'device->rad_info.chip_class < GFX10'),
    Extension('VK_EXT_sampler_filter_minmax',             1, True),
    Extension('VK_EXT_scalar_block_layout',               1, 'device->rad_info.chip_class >= GFX7'),
    Extension('VK_EXT_shader_demote_to_helper_invocation',1, 'device->use_aco'),
    Extension('VK_EXT_shader_viewport_index_layer',       1, True),
    Extension('VK_EXT_shader_stencil_export',             1, True),
    Extension('VK_EXT_shader_subgroup_ballot',            1, True),
    Extension('VK_EXT_shader_subgroup_vote',              1, True),
    Extension('VK_EXT_subgroup_size_control',             2, '!device->use_aco'),
    Extension('VK_EXT_texel_buffer_alignment',            1, True),
    Extension('VK_EXT_transform_feedback',                1, True),
    Extension('VK_EXT_vertex_attribute_divisor',          3, True),
    Extension('VK_EXT_ycbcr_image_arrays',                1, True),
    Extension('VK_AMD_buffer_marker',                     1, True),
    Extension('VK_AMD_device_coherent_memory',            1, True),
    Extension('VK_AMD_draw_indirect_count',               1, True),
    Extension('VK_AMD_gcn_shader',                        1, True),
    Extension('VK_AMD_gpu_shader_half_float',             1, '!device->use_aco && device->rad_info.has_double_rate_fp16'),
    Extension('VK_AMD_gpu_shader_int16',                  1, '!device->use_aco && device->rad_info.has_double_rate_fp16'),
    Extension('VK_AMD_memory_overallocation_behavior',    1, True),
    # Disable mixed attachment samples on GFX6-GFX7 until the CTS failures have been resolved.
    Extension('VK_AMD_mixed_attachment_samples',          1, 'device->rad_info.chip_class >= GFX8'),
    Extension('VK_AMD_rasterization_order',               1, 'device->rad_info.has_out_of_order_rast'),
    Extension('VK_AMD_shader_ballot',                     1, 'device->use_shader_ballot'),
    Extension('VK_AMD_shader_core_properties',            1, True),
    Extension('VK_AMD_shader_core_properties2',           1, True),
    Extension('VK_AMD_shader_explicit_vertex_parameter',  1, True),
    Extension('VK_AMD_shader_image_load_store_lod',       1, True),
    Extension('VK_AMD_shader_fragment_mask',              1, True),
    Extension('VK_AMD_shader_info',                       1, True),
    Extension('VK_AMD_shader_trinary_minmax',             1, True),
    Extension('VK_GOOGLE_decorate_string',                1, True),
    Extension('VK_GOOGLE_hlsl_functionality1',            1, True),
    Extension('VK_GOOGLE_user_type',                      1, True),
    Extension('VK_NV_compute_shader_derivatives',         1, True),
]

class VkVersion:
    def __init__(self, string):
        split = string.split('.')
        self.major = int(split[0])
        self.minor = int(split[1])
        if len(split) > 2:
            assert len(split) == 3
            self.patch = int(split[2])
        else:
            self.patch = None

        # Sanity check.  The range bits are required by the definition of the
        # VK_MAKE_VERSION macro
        assert self.major < 1024 and self.minor < 1024
        assert self.patch is None or self.patch < 4096
        assert(str(self) == string)

    def __str__(self):
        ver_list = [str(self.major), str(self.minor)]
        if self.patch is not None:
            ver_list.append(str(self.patch))
        return '.'.join(ver_list)

    def c_vk_version(self):
        patch = self.patch if self.patch is not None else 0
        ver_list = [str(self.major), str(self.minor), str(patch)]
        return 'VK_MAKE_VERSION(' + ', '.join(ver_list) + ')'

    def __int_ver(self):
        # This is just an expansion of VK_VERSION
        patch = self.patch if self.patch is not None else 0
        return (self.major << 22) | (self.minor << 12) | patch

    def __gt__(self, other):
        # If only one of them has a patch version, "ignore" it by making
        # other's patch version match self.
        if (self.patch is None) != (other.patch is None):
            other = copy.copy(other)
            other.patch = self.patch

        return self.__int_ver() > other.__int_ver()


MAX_API_VERSION = VkVersion('0.0.0')
for version in API_VERSIONS:
    version.version = VkVersion(version.version)
    assert version.version > MAX_API_VERSION
    MAX_API_VERSION = version.version

def _init_exts_from_xml(xml):
    """ Walk the Vulkan XML and fill out extra extension information. """

    xml = et.parse(xml)

    ext_name_map = {}
    for ext in EXTENSIONS:
        ext_name_map[ext.name] = ext

    for ext_elem in xml.findall('.extensions/extension'):
        ext_name = ext_elem.attrib['name']
        if ext_name not in ext_name_map:
            continue

        ext = ext_name_map[ext_name]
        ext.type = ext_elem.attrib['type']
        ext.promotedto = ext_elem.attrib.get('promotedto', None)
        try:
            ext.requires = ext_elem.attrib['requires'].split(',')
        except KeyError:
            ext.requires = []

    def extra_deps(ext):
        if ext.type == 'instance':
            check = 'instance->enabled_extensions.{}'.format(ext.name[3:])
            if ext.promotedto is not None:
                # the xml contains values like VK_VERSION_1_1, but we need to
                # translate them to VK_API_VERSION_1_1 for the apiVersion check
                api_ver = ext.promotedto.replace('VK_VER', 'VK_API_VER')
                check = '({} || instance->apiVersion >= {})'.format(check, api_ver)
            return set([check])

        deps = set()
        for dep in ext.requires:
            deps |= extra_deps(ext_name_map[dep])

        return deps

    for ext in EXTENSIONS:
        if ext.type == 'device':
            ext.enable = '(' + ext.enable + ')'
            for dep in extra_deps(ext):
                ext.enable += ' && ' + dep

# Mapping between extension name and the android version in which the extension
# was whitelisted in Android CTS.
allowed_android_version = {
    # Allowed Instance KHR Extensions
    "VK_KHR_surface": 26,
    "VK_KHR_display": 26,
    "VK_KHR_android_surface": 26,
    "VK_KHR_mir_surface": 26,
    "VK_KHR_wayland_surface": 26,
    "VK_KHR_win32_surface": 26,
    "VK_KHR_xcb_surface": 26,
    "VK_KHR_xlib_surface": 26,
    "VK_KHR_get_physical_device_properties2": 26,
    "VK_KHR_get_surface_capabilities2": 26,
    "VK_KHR_external_memory_capabilities": 28,
    "VK_KHR_external_semaphore_capabilities": 28,
    "VK_KHR_external_fence_capabilities": 28,
    "VK_KHR_device_group_creation": 28,
    "VK_KHR_get_display_properties2": 29,
    "VK_KHR_surface_protected_capabilities": 29,

    # Allowed Device KHR Extensions
    "VK_KHR_swapchain": 26,
    "VK_KHR_display_swapchain": 26,
    "VK_KHR_sampler_mirror_clamp_to_edge": 26,
    "VK_KHR_shader_draw_parameters": 26,
    "VK_KHR_shader_float_controls": 29,
    "VK_KHR_shader_float16_int8": 29,
    "VK_KHR_maintenance1": 26,
    "VK_KHR_push_descriptor": 26,
    "VK_KHR_descriptor_update_template": 26,
    "VK_KHR_incremental_present": 26,
    "VK_KHR_shared_presentable_image": 26,
    "VK_KHR_storage_buffer_storage_class": 28,
    "VK_KHR_8bit_storage": 29,
    "VK_KHR_16bit_storage": 28,
    "VK_KHR_get_memory_requirements2": 28,
    "VK_KHR_external_memory": 28,
    "VK_KHR_external_memory_fd": 28,
    "VK_KHR_external_memory_win32": 28,
    "VK_KHR_external_semaphore": 28,
    "VK_KHR_external_semaphore_fd": 28,
    "VK_KHR_external_semaphore_win32": 28,
    "VK_KHR_external_fence": 28,
    "VK_KHR_external_fence_fd": 28,
    "VK_KHR_external_fence_win32": 28,
    "VK_KHR_win32_keyed_mutex": 28,
    "VK_KHR_dedicated_allocation": 28,
    "VK_KHR_variable_pointers": 28,
    "VK_KHR_relaxed_block_layout": 28,
    "VK_KHR_bind_memory2": 28,
    "VK_KHR_maintenance2": 28,
    "VK_KHR_image_format_list": 28,
    "VK_KHR_sampler_ycbcr_conversion": 28,
    "VK_KHR_device_group": 28,
    "VK_KHR_multiview": 28,
    "VK_KHR_maintenance3": 28,
    "VK_KHR_draw_indirect_count": 28,
    "VK_KHR_create_renderpass2": 28,
    "VK_KHR_depth_stencil_resolve": 29,
    "VK_KHR_driver_properties": 28,
    "VK_KHR_swapchain_mutable_format": 29,
    "VK_KHR_shader_atomic_int64": 29,
    "VK_KHR_vulkan_memory_model": 29,

    "VK_GOOGLE_display_timing": 26,
    "VK_ANDROID_native_buffer": 26,
    "VK_ANDROID_external_memory_android_hardware_buffer": 28,
}

# Extensions with these prefixes are checked in Android CTS, and thus must be
# whitelisted per the preceding dict.
android_extension_whitelist_prefixes = (
    "VK_KHX",
    "VK_KHR",
    "VK_GOOGLE",
    "VK_ANDROID"
)

def GetExtensionCondition(ext_name, condition):
    """ If |ext_name| is an extension that Android CTS cares about, prepend
        a condition to ensure that the extension is only enabled for Android
        versions in which the extension is whitelisted in CTS. """
    if not ext_name.startswith(android_extension_whitelist_prefixes):
        return condition
    allowed_version = allowed_android_version.get(ext_name, 9999)
    return "(!ANDROID || ANDROID_API_LEVEL >= %d) && (%s)" % (allowed_version,
                                                              condition)

_TEMPLATE_H = Template(COPYRIGHT + """
#ifndef RADV_EXTENSIONS_H
#define RADV_EXTENSIONS_H

enum {
   RADV_INSTANCE_EXTENSION_COUNT = ${len(instance_extensions)},
   RADV_DEVICE_EXTENSION_COUNT = ${len(device_extensions)},
};

struct radv_instance_extension_table {
   union {
      bool extensions[RADV_INSTANCE_EXTENSION_COUNT];
      struct {
%for ext in instance_extensions:
        bool ${ext.name[3:]};
%endfor
      };
   };
};

struct radv_device_extension_table {
   union {
      bool extensions[RADV_DEVICE_EXTENSION_COUNT];
      struct {
%for ext in device_extensions:
        bool ${ext.name[3:]};
%endfor
      };
   };
};

extern const VkExtensionProperties radv_instance_extensions[RADV_INSTANCE_EXTENSION_COUNT];
extern const VkExtensionProperties radv_device_extensions[RADV_DEVICE_EXTENSION_COUNT];
extern const struct radv_instance_extension_table radv_supported_instance_extensions;


struct radv_physical_device;

void radv_fill_device_extension_table(const struct radv_physical_device *device,
                                      struct radv_device_extension_table* table);
#endif
""")

_TEMPLATE_C = Template(COPYRIGHT + """
#include "radv_private.h"

#include "vk_util.h"

/* Convert the VK_USE_PLATFORM_* defines to booleans */
%for platform in ['ANDROID_KHR', 'WAYLAND_KHR', 'XCB_KHR', 'XLIB_KHR', 'DISPLAY_KHR', 'XLIB_XRANDR_EXT']:
#ifdef VK_USE_PLATFORM_${platform}
#   undef VK_USE_PLATFORM_${platform}
#   define VK_USE_PLATFORM_${platform} true
#else
#   define VK_USE_PLATFORM_${platform} false
#endif
%endfor

/* And ANDROID too */
#ifdef ANDROID
#   undef ANDROID
#   define ANDROID true
#else
#   define ANDROID false
#   define ANDROID_API_LEVEL 0
#endif

#define RADV_HAS_SURFACE (VK_USE_PLATFORM_WAYLAND_KHR || \\
                         VK_USE_PLATFORM_XCB_KHR || \\
                         VK_USE_PLATFORM_XLIB_KHR || \\
                         VK_USE_PLATFORM_DISPLAY_KHR)

static const uint32_t MAX_API_VERSION = ${MAX_API_VERSION.c_vk_version()};

const VkExtensionProperties radv_instance_extensions[RADV_INSTANCE_EXTENSION_COUNT] = {
%for ext in instance_extensions:
   {"${ext.name}", ${ext.ext_version}},
%endfor
};

const VkExtensionProperties radv_device_extensions[RADV_DEVICE_EXTENSION_COUNT] = {
%for ext in device_extensions:
   {"${ext.name}", ${ext.ext_version}},
%endfor
};

const struct radv_instance_extension_table radv_supported_instance_extensions = {
%for ext in instance_extensions:
   .${ext.name[3:]} = ${GetExtensionCondition(ext.name, ext.enable)},
%endfor
};

void radv_fill_device_extension_table(const struct radv_physical_device *device,
                                      struct radv_device_extension_table* table)
{
   const struct radv_instance *instance = device->instance;
%for ext in device_extensions:
   table->${ext.name[3:]} = ${GetExtensionCondition(ext.name, ext.enable)};
%endfor
}

VkResult radv_EnumerateInstanceVersion(
    uint32_t*                                   pApiVersion)
{
    *pApiVersion = MAX_API_VERSION;
    return VK_SUCCESS;
}

uint32_t
radv_physical_device_api_version(struct radv_physical_device *dev)
{
    uint32_t version = 0;

    uint32_t override = vk_get_version_override();
    if (override)
        return MIN2(override, MAX_API_VERSION);

%for version in API_VERSIONS:
    if (!(${version.enable}))
        return version;
    version = ${version.version.c_vk_version()};

%endfor
    return version;
}
""")

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--out-c', help='Output C file.', required=True)
    parser.add_argument('--out-h', help='Output H file.', required=True)
    parser.add_argument('--xml',
                        help='Vulkan API XML file.',
                        required=True,
                        action='append',
                        dest='xml_files')
    args = parser.parse_args()

    for filename in args.xml_files:
        _init_exts_from_xml(filename)

    for ext in EXTENSIONS:
        assert ext.type == 'instance' or ext.type == 'device'

    template_env = {
        'API_VERSIONS': API_VERSIONS,
        'MAX_API_VERSION': MAX_API_VERSION,
        'instance_extensions': [e for e in EXTENSIONS if e.type == 'instance'],
        'device_extensions': [e for e in EXTENSIONS if e.type == 'device'],
        'GetExtensionCondition': GetExtensionCondition,
    }

    with open(args.out_c, 'w') as f:
        f.write(_TEMPLATE_C.render(**template_env))
    with open(args.out_h, 'w') as f:
        f.write(_TEMPLATE_H.render(**template_env))
