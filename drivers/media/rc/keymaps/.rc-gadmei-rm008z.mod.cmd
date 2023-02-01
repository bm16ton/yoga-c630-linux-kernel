cmd_drivers/media/rc/keymaps/rc-gadmei-rm008z.mod := printf '%s\n'   rc-gadmei-rm008z.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-gadmei-rm008z.mod
