cmd_drivers/media/rc/keymaps/rc-pinnacle-grey.mod := printf '%s\n'   rc-pinnacle-grey.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pinnacle-grey.mod
