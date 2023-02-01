cmd_drivers/media/rc/keymaps/rc-pctv-sedna.mod := printf '%s\n'   rc-pctv-sedna.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-pctv-sedna.mod
