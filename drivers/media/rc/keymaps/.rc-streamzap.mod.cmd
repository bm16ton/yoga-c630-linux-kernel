cmd_drivers/media/rc/keymaps/rc-streamzap.mod := printf '%s\n'   rc-streamzap.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-streamzap.mod
