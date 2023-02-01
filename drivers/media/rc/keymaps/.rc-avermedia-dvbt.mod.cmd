cmd_drivers/media/rc/keymaps/rc-avermedia-dvbt.mod := printf '%s\n'   rc-avermedia-dvbt.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-avermedia-dvbt.mod
