cmd_drivers/media/rc/keymaps/rc-imon-mce.mod := printf '%s\n'   rc-imon-mce.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-imon-mce.mod
