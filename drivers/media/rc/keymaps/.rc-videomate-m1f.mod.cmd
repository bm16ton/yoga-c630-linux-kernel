cmd_drivers/media/rc/keymaps/rc-videomate-m1f.mod := printf '%s\n'   rc-videomate-m1f.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-videomate-m1f.mod
