cmd_drivers/media/rc/keymaps/rc-cinergy-1400.mod := printf '%s\n'   rc-cinergy-1400.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-cinergy-1400.mod
