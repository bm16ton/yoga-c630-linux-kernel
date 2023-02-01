cmd_drivers/iommu/arm/built-in.a := rm -f drivers/iommu/arm/built-in.a;  printf "drivers/iommu/arm/%s " arm-smmu/built-in.a arm-smmu-v3/built-in.a | xargs ar cDPrST drivers/iommu/arm/built-in.a
