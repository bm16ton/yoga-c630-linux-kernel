cmd_drivers/media/rc/keymaps/rc-imon-pad.mod := printf '%s\n'   rc-imon-pad.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-imon-pad.mod
