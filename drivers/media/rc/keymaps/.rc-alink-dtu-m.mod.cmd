cmd_drivers/media/rc/keymaps/rc-alink-dtu-m.mod := printf '%s\n'   rc-alink-dtu-m.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-alink-dtu-m.mod
