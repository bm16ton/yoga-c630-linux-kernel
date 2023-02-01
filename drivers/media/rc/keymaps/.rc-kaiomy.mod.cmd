cmd_drivers/media/rc/keymaps/rc-kaiomy.mod := printf '%s\n'   rc-kaiomy.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-kaiomy.mod
