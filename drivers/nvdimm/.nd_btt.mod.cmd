cmd_drivers/nvdimm/nd_btt.mod := printf '%s\n'   btt.o | awk '!x[$$0]++ { print("drivers/nvdimm/"$$0) }' > drivers/nvdimm/nd_btt.mod
