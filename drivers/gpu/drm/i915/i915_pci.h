/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2021 Intel Corporation
 */

#ifndef __I915_PCI_H__
#define __I915_PCI_H__

<<<<<<< HEAD
#include <linux/types.h>

struct pci_dev;

int i915_pci_register_driver(void);
void i915_pci_unregister_driver(void);

bool i915_pci_resource_valid(struct pci_dev *pdev, int bar);

=======
int i915_pci_register_driver(void);
void i915_pci_unregister_driver(void);

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
#endif /* __I915_PCI_H__ */
