cmd_drivers/media/rc/keymaps/rc-cinergy.mod := printf '%s\n'   rc-cinergy.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-cinergy.mod
