cmd_drivers/media/rc/keymaps/rc-minix-neo.mod := printf '%s\n'   rc-minix-neo.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-minix-neo.mod
