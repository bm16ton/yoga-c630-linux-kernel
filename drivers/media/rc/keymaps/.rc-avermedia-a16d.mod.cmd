cmd_drivers/media/rc/keymaps/rc-avermedia-a16d.mod := printf '%s\n'   rc-avermedia-a16d.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-avermedia-a16d.mod
