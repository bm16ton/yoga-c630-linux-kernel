cmd_drivers/media/rc/keymaps/rc-tt-1500.mod := printf '%s\n'   rc-tt-1500.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tt-1500.mod
