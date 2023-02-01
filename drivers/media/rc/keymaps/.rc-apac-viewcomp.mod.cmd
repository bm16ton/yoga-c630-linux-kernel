cmd_drivers/media/rc/keymaps/rc-apac-viewcomp.mod := printf '%s\n'   rc-apac-viewcomp.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-apac-viewcomp.mod
