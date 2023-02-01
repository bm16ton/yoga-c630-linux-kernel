cmd_drivers/media/rc/keymaps/rc-rc6-mce.mod := printf '%s\n'   rc-rc6-mce.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-rc6-mce.mod
