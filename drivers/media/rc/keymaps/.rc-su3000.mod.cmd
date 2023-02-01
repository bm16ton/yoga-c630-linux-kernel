cmd_drivers/media/rc/keymaps/rc-su3000.mod := printf '%s\n'   rc-su3000.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-su3000.mod
