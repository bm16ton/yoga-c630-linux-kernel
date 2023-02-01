cmd_drivers/media/rc/keymaps/rc-terratec-slim.mod := printf '%s\n'   rc-terratec-slim.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-terratec-slim.mod
