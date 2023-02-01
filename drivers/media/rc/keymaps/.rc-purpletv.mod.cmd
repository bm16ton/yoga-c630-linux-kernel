cmd_drivers/media/rc/keymaps/rc-purpletv.mod := printf '%s\n'   rc-purpletv.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-purpletv.mod
