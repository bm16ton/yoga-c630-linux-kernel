cmd_drivers/media/rc/keymaps/rc-tivo.mod := printf '%s\n'   rc-tivo.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tivo.mod
