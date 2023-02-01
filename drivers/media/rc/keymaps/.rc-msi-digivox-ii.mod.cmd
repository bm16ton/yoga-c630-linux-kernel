cmd_drivers/media/rc/keymaps/rc-msi-digivox-ii.mod := printf '%s\n'   rc-msi-digivox-ii.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-msi-digivox-ii.mod
