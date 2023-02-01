cmd_drivers/media/rc/keymaps/rc-hauppauge.mod := printf '%s\n'   rc-hauppauge.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-hauppauge.mod
