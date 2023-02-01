cmd_drivers/media/rc/keymaps/rc-pine64.mod := printf '%s\n'   rc-pine64.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pine64.mod
