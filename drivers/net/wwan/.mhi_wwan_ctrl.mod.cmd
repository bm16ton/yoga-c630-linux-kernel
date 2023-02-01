cmd_drivers/net/wwan/mhi_wwan_ctrl.mod := printf '%s\n'   mhi_wwan_ctrl.o | awk '!x[$$0]++ { print("drivers/net/wwan/"$$0) }' > drivers/net/wwan/mhi_wwan_ctrl.mod
