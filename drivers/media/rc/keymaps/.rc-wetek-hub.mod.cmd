cmd_drivers/media/rc/keymaps/rc-wetek-hub.mod := printf '%s\n'   rc-wetek-hub.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-wetek-hub.mod
