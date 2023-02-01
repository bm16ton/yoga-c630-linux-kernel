cmd_drivers/media/rc/keymaps/rc-kworld-pc150u.mod := printf '%s\n'   rc-kworld-pc150u.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-kworld-pc150u.mod
