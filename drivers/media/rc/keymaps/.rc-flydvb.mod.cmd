cmd_drivers/media/rc/keymaps/rc-flydvb.mod := printf '%s\n'   rc-flydvb.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-flydvb.mod
