cmd_drivers/media/rc/keymaps/rc-iodata-bctv7e.mod := printf '%s\n'   rc-iodata-bctv7e.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-iodata-bctv7e.mod
