cmd_drivers/media/rc/keymaps/rc-dm1105-nec.mod := printf '%s\n'   rc-dm1105-nec.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-dm1105-nec.mod
