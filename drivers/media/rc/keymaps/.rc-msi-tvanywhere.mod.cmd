cmd_drivers/media/rc/keymaps/rc-msi-tvanywhere.mod := printf '%s\n'   rc-msi-tvanywhere.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-msi-tvanywhere.mod
