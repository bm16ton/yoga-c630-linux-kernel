cmd_drivers/media/rc/keymaps/rc-dvico-mce.mod := printf '%s\n'   rc-dvico-mce.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-dvico-mce.mod
