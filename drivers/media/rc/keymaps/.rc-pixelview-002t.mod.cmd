cmd_drivers/media/rc/keymaps/rc-pixelview-002t.mod := printf '%s\n'   rc-pixelview-002t.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pixelview-002t.mod
