cmd_drivers/media/rc/keymaps/rc-ati-x10.mod := printf '%s\n'   rc-ati-x10.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-ati-x10.mod
