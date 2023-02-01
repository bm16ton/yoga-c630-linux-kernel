cmd_drivers/media/rc/keymaps/rc-eztv.mod := printf '%s\n'   rc-eztv.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-eztv.mod
