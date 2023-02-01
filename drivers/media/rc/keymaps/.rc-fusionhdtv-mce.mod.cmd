cmd_drivers/media/rc/keymaps/rc-fusionhdtv-mce.mod := printf '%s\n'   rc-fusionhdtv-mce.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-fusionhdtv-mce.mod
