cmd_drivers/media/rc/keymaps/rc-flyvideo.mod := printf '%s\n'   rc-flyvideo.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-flyvideo.mod
