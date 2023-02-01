/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2022 Intel Corporation
 */

#ifndef __SYSFS_GT_H__
#define __SYSFS_GT_H__

#include <linux/ctype.h>
#include <linux/kobject.h>

#include "i915_gem.h" /* GEM_BUG_ON() */
<<<<<<< HEAD
#include "intel_gt_types.h"
=======
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

struct intel_gt;

bool is_object_gt(struct kobject *kobj);

struct drm_i915_private *kobj_to_i915(struct kobject *kobj);

struct kobject *
intel_gt_create_kobj(struct intel_gt *gt,
		     struct kobject *dir,
		     const char *name);

<<<<<<< HEAD
static inline struct intel_gt *kobj_to_gt(struct kobject *kobj)
{
	return container_of(kobj, struct intel_gt, sysfs_gt);
}

void intel_gt_sysfs_register(struct intel_gt *gt);
void intel_gt_sysfs_unregister(struct intel_gt *gt);
struct intel_gt *intel_gt_sysfs_get_drvdata(struct kobject *kobj,
=======
void intel_gt_sysfs_register(struct intel_gt *gt);
void intel_gt_sysfs_unregister(struct intel_gt *gt);
struct intel_gt *intel_gt_sysfs_get_drvdata(struct device *dev,
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
					    const char *name);

#endif /* SYSFS_GT_H */
