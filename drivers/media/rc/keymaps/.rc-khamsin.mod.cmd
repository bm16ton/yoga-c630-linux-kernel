cmd_drivers/media/rc/keymaps/rc-khamsin.mod := printf '%s\n'   rc-khamsin.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-khamsin.mod
