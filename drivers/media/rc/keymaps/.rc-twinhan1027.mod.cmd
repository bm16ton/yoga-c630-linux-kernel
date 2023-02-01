cmd_drivers/media/rc/keymaps/rc-twinhan1027.mod := printf '%s\n'   rc-twinhan1027.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-twinhan1027.mod
