cmd_drivers/media/rc/keymaps/rc-winfast.mod := printf '%s\n'   rc-winfast.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-winfast.mod
