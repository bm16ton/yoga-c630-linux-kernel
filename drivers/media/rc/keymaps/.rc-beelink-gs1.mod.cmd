cmd_drivers/media/rc/keymaps/rc-beelink-gs1.mod := printf '%s\n'   rc-beelink-gs1.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-beelink-gs1.mod
