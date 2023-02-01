cmd_drivers/media/rc/keymaps/rc-pinnacle-color.mod := printf '%s\n'   rc-pinnacle-color.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pinnacle-color.mod
