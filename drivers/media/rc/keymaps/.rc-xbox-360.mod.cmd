cmd_drivers/media/rc/keymaps/rc-xbox-360.mod := printf '%s\n'   rc-xbox-360.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-xbox-360.mod
