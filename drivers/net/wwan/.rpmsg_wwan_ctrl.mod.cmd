cmd_drivers/net/wwan/rpmsg_wwan_ctrl.mod := printf '%s\n'   rpmsg_wwan_ctrl.o | awk '!x[$$0]++ { print("drivers/net/wwan/"$$0) }' > drivers/net/wwan/rpmsg_wwan_ctrl.mod
