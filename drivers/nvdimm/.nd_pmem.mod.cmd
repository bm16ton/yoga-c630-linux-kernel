cmd_drivers/nvdimm/nd_pmem.mod := printf '%s\n'   pmem.o | awk '!x[$$0]++ { print("drivers/nvdimm/"$$0) }' > drivers/nvdimm/nd_pmem.mod
