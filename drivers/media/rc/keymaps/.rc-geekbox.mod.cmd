cmd_drivers/media/rc/keymaps/rc-geekbox.mod := printf '%s\n'   rc-geekbox.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-geekbox.mod
