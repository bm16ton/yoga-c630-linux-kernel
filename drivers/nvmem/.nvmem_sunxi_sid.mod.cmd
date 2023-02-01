cmd_drivers/nvmem/nvmem_sunxi_sid.mod := printf '%s\n'   sunxi_sid.o | awk '!x[$$0]++ { print("drivers/nvmem/"$$0) }' > drivers/nvmem/nvmem_sunxi_sid.mod
