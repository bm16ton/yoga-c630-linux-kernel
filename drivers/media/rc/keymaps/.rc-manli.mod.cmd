cmd_drivers/media/rc/keymaps/rc-manli.mod := printf '%s\n'   rc-manli.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-manli.mod
