cmd_drivers/media/rc/keymaps/rc-tanix-tx5max.mod := printf '%s\n'   rc-tanix-tx5max.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-tanix-tx5max.mod
