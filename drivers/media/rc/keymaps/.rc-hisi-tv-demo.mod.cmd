cmd_drivers/media/rc/keymaps/rc-hisi-tv-demo.mod := printf '%s\n'   rc-hisi-tv-demo.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-hisi-tv-demo.mod
