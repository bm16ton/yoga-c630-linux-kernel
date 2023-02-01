cmd_drivers/media/rc/keymaps/rc-proteus-2309.mod := printf '%s\n'   rc-proteus-2309.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-proteus-2309.mod
