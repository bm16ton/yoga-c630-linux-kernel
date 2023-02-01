cmd_drivers/net/wireless/ti/wl1251/wl1251_spi.mod := printf '%s\n'   spi.o | awk '!x[$$0]++ { print("drivers/net/wireless/ti/wl1251/"$$0) }' > drivers/net/wireless/ti/wl1251/wl1251_spi.mod
