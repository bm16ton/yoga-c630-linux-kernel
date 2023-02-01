cmd_drivers/media/rc/keymaps/rc-npgtech.mod := printf '%s\n'   rc-npgtech.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-npgtech.mod
