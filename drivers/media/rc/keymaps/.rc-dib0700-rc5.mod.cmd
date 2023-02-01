cmd_drivers/media/rc/keymaps/rc-dib0700-rc5.mod := printf '%s\n'   rc-dib0700-rc5.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-dib0700-rc5.mod
