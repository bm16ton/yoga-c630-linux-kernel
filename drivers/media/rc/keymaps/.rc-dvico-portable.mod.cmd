cmd_drivers/media/rc/keymaps/rc-dvico-portable.mod := printf '%s\n'   rc-dvico-portable.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-dvico-portable.mod
