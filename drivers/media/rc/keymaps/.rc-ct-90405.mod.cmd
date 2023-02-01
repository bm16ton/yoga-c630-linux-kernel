cmd_drivers/media/rc/keymaps/rc-ct-90405.mod := printf '%s\n'   rc-ct-90405.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-ct-90405.mod
