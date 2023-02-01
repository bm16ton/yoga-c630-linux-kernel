cmd_drivers/media/rc/keymaps/rc-avertv-303.mod := printf '%s\n'   rc-avertv-303.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-avertv-303.mod
