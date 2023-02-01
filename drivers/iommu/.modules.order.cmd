cmd_drivers/iommu/modules.order := {   cat drivers/iommu/amd/modules.order;   cat drivers/iommu/intel/modules.order;   cat drivers/iommu/arm/modules.order; :; } > drivers/iommu/modules.order
