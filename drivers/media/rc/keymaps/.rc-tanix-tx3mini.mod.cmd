cmd_drivers/media/rc/keymaps/rc-tanix-tx3mini.mod := printf '%s\n'   rc-tanix-tx3mini.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tanix-tx3mini.mod
