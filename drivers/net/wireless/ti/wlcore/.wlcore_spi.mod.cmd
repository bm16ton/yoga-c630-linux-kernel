cmd_drivers/net/wireless/ti/wlcore/wlcore_spi.mod := printf '%s\n'   spi.o | awk '!x[$$0]++ { print("drivers/net/wireless/ti/wlcore/"$$0) }' > drivers/net/wireless/ti/wlcore/wlcore_spi.mod
