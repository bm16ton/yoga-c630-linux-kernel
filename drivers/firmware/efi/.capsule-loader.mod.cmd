cmd_drivers/firmware/efi/capsule-loader.mod := printf '%s\n'   capsule-loader.o | awk '!x[$$0]++ { print("drivers/firmware/efi/"$$0) }' > drivers/firmware/efi/capsule-loader.mod
