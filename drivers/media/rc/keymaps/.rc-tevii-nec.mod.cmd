cmd_drivers/media/rc/keymaps/rc-tevii-nec.mod := printf '%s\n'   rc-tevii-nec.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tevii-nec.mod
