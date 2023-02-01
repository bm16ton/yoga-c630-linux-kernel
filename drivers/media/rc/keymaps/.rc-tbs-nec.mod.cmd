cmd_drivers/media/rc/keymaps/rc-tbs-nec.mod := printf '%s\n'   rc-tbs-nec.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tbs-nec.mod
