cmd_drivers/vfio/vfio_iommu_type1.mod := printf '%s\n'   vfio_iommu_type1.o | awk '!x[$$0]++ { print("drivers/vfio/"$$0) }' > drivers/vfio/vfio_iommu_type1.mod
