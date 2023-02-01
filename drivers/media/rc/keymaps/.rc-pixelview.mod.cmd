cmd_drivers/media/rc/keymaps/rc-pixelview.mod := printf '%s\n'   rc-pixelview.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pixelview.mod
