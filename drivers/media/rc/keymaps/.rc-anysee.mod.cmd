cmd_drivers/media/rc/keymaps/rc-anysee.mod := printf '%s\n'   rc-anysee.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-anysee.mod
