cmd_drivers/media/rc/keymaps/rc-technisat-ts35.mod := printf '%s\n'   rc-technisat-ts35.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-technisat-ts35.mod
