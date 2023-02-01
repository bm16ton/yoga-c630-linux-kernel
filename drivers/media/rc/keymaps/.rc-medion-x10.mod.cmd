cmd_drivers/media/rc/keymaps/rc-medion-x10.mod := printf '%s\n'   rc-medion-x10.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-medion-x10.mod
