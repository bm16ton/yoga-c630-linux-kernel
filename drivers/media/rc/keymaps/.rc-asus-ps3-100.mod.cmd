cmd_drivers/media/rc/keymaps/rc-asus-ps3-100.mod := printf '%s\n'   rc-asus-ps3-100.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-asus-ps3-100.mod
