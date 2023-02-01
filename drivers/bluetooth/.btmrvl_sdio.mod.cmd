cmd_drivers/bluetooth/btmrvl_sdio.mod := printf '%s\n'   btmrvl_sdio.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/btmrvl_sdio.mod
