cmd_drivers/net/wireless/rndis_wlan.mod := printf '%s\n'   rndis_wlan.o | awk '!x[$$0]++ { print("drivers/net/wireless/"$$0) }' > drivers/net/wireless/rndis_wlan.mod
