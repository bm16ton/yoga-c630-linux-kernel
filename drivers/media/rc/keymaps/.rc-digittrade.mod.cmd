cmd_drivers/media/rc/keymaps/rc-digittrade.mod := printf '%s\n'   rc-digittrade.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-digittrade.mod
