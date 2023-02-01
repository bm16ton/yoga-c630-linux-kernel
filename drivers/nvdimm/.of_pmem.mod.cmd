cmd_drivers/nvdimm/of_pmem.mod := printf '%s\n'   of_pmem.o | awk '!x[$$0]++ { print("drivers/nvdimm/"$$0) }' > drivers/nvdimm/of_pmem.mod
