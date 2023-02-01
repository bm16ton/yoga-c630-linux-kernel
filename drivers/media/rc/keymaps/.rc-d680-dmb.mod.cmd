cmd_drivers/media/rc/keymaps/rc-d680-dmb.mod := printf '%s\n'   rc-d680-dmb.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-d680-dmb.mod
