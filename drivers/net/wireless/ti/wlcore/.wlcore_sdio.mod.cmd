cmd_drivers/net/wireless/ti/wlcore/wlcore_sdio.mod := printf '%s\n'   sdio.o | awk '!x[$$0]++ { print("drivers/net/wireless/ti/wlcore/"$$0) }' > drivers/net/wireless/ti/wlcore/wlcore_sdio.mod
