cmd_drivers/media/rc/keymaps/rc-evga-indtube.mod := printf '%s\n'   rc-evga-indtube.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-evga-indtube.mod
