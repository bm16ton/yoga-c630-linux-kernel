cmd_drivers/net/wwan/mhi_wwan_mbim.mod := printf '%s\n'   mhi_wwan_mbim.o | awk '!x[$$0]++ { print("drivers/net/wwan/"$$0) }' > drivers/net/wwan/mhi_wwan_mbim.mod
