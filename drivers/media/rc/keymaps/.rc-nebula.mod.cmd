cmd_drivers/media/rc/keymaps/rc-nebula.mod := printf '%s\n'   rc-nebula.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-nebula.mod
