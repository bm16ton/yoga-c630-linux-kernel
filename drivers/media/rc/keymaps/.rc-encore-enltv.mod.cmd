cmd_drivers/media/rc/keymaps/rc-encore-enltv.mod := printf '%s\n'   rc-encore-enltv.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-encore-enltv.mod
