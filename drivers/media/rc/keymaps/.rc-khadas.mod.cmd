cmd_drivers/media/rc/keymaps/rc-khadas.mod := printf '%s\n'   rc-khadas.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-khadas.mod
