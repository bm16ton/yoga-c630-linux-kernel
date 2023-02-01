cmd_drivers/media/rc/keymaps/rc-x96max.mod := printf '%s\n'   rc-x96max.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-x96max.mod
