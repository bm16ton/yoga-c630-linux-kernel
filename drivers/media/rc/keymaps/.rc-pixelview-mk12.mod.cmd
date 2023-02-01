cmd_drivers/media/rc/keymaps/rc-pixelview-mk12.mod := printf '%s\n'   rc-pixelview-mk12.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pixelview-mk12.mod
