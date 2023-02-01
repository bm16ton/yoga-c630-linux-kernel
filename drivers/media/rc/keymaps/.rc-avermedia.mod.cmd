cmd_drivers/media/rc/keymaps/rc-avermedia.mod := printf '%s\n'   rc-avermedia.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-avermedia.mod
