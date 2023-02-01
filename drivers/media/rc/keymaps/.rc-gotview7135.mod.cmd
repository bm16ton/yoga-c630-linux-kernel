cmd_drivers/media/rc/keymaps/rc-gotview7135.mod := printf '%s\n'   rc-gotview7135.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-gotview7135.mod
