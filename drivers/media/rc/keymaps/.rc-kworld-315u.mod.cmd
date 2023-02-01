cmd_drivers/media/rc/keymaps/rc-kworld-315u.mod := printf '%s\n'   rc-kworld-315u.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-kworld-315u.mod
