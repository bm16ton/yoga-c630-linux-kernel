cmd_drivers/firmware/efi/efibc.mod := printf '%s\n'   efibc.o | awk '!x[$$0]++ { print("drivers/firmware/efi/"$$0) }' > drivers/firmware/efi/efibc.mod
