cmd_drivers/media/rc/keymaps/rc-it913x-v1.mod := printf '%s\n'   rc-it913x-v1.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-it913x-v1.mod
