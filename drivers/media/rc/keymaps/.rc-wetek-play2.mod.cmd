cmd_drivers/media/rc/keymaps/rc-wetek-play2.mod := printf '%s\n'   rc-wetek-play2.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-wetek-play2.mod
