cmd_drivers/media/rc/keymaps/rc-pv951.mod := printf '%s\n'   rc-pv951.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pv951.mod
