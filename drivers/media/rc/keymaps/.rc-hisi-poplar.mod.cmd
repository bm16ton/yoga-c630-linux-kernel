cmd_drivers/media/rc/keymaps/rc-hisi-poplar.mod := printf '%s\n'   rc-hisi-poplar.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-hisi-poplar.mod
