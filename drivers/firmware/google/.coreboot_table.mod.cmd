cmd_drivers/firmware/google/coreboot_table.mod := printf '%s\n'   coreboot_table.o | awk '!x[$$0]++ { print("drivers/firmware/google/"$$0) }' > drivers/firmware/google/coreboot_table.mod
