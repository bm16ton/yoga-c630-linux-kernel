cmd_drivers/nvdimm/virtio_pmem.mod := printf '%s\n'   virtio_pmem.o | awk '!x[$$0]++ { print("drivers/nvdimm/"$$0) }' > drivers/nvdimm/virtio_pmem.mod
