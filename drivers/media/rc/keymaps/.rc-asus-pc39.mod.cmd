cmd_drivers/media/rc/keymaps/rc-asus-pc39.mod := printf '%s\n'   rc-asus-pc39.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-asus-pc39.mod
