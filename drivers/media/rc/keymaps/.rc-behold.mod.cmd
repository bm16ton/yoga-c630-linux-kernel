cmd_drivers/media/rc/keymaps/rc-behold.mod := printf '%s\n'   rc-behold.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-behold.mod
