/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_ACPI_H__
#define __INTEL_ACPI_H__

struct drm_i915_private;

#ifdef CONFIG_ACPI
void intel_register_dsm_handler(void);
void intel_unregister_dsm_handler(void);
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915);
void intel_acpi_device_id_update(struct drm_i915_private *i915);
void intel_acpi_assign_connector_fwnodes(struct drm_i915_private *i915);
<<<<<<< HEAD
void intel_acpi_video_register(struct drm_i915_private *i915);
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#else
static inline void intel_register_dsm_handler(void) { return; }
static inline void intel_unregister_dsm_handler(void) { return; }
static inline
void intel_dsm_get_bios_data_funcs_supported(struct drm_i915_private *i915) { return; }
static inline
void intel_acpi_device_id_update(struct drm_i915_private *i915) { return; }
static inline
void intel_acpi_assign_connector_fwnodes(struct drm_i915_private *i915) { return; }
<<<<<<< HEAD
static inline
void intel_acpi_video_register(struct drm_i915_private *i915) { return; }
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif /* CONFIG_ACPI */

#endif /* __INTEL_ACPI_H__ */
