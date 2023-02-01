cmd_drivers/dax/dax_pmem.mod := printf '%s\n'   pmem.o | awk '!x[$$0]++ { print("drivers/dax/"$$0) }' > drivers/dax/dax_pmem.mod
