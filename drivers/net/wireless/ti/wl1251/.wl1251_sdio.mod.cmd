cmd_drivers/net/wireless/ti/wl1251/wl1251_sdio.mod := printf '%s\n'   sdio.o | awk '!x[$$0]++ { print("drivers/net/wireless/ti/wl1251/"$$0) }' > drivers/net/wireless/ti/wl1251/wl1251_sdio.mod
