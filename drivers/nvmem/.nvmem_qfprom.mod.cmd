cmd_drivers/nvmem/nvmem_qfprom.mod := printf '%s\n'   qfprom.o | awk '!x[$$0]++ { print("drivers/nvmem/"$$0) }' > drivers/nvmem/nvmem_qfprom.mod
