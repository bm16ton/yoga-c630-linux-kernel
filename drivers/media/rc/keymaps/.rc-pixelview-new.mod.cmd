cmd_drivers/media/rc/keymaps/rc-pixelview-new.mod := printf '%s\n'   rc-pixelview-new.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pixelview-new.mod
