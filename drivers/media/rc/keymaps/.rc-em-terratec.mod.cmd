cmd_drivers/media/rc/keymaps/rc-em-terratec.mod := printf '%s\n'   rc-em-terratec.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-em-terratec.mod
