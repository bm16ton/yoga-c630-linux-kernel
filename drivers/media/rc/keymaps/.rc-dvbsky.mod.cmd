cmd_drivers/media/rc/keymaps/rc-dvbsky.mod := printf '%s\n'   rc-dvbsky.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-dvbsky.mod
