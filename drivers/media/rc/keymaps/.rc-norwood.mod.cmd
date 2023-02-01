cmd_drivers/media/rc/keymaps/rc-norwood.mod := printf '%s\n'   rc-norwood.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-norwood.mod
