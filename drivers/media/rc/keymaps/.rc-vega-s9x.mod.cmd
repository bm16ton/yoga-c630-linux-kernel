cmd_drivers/media/rc/keymaps/rc-vega-s9x.mod := printf '%s\n'   rc-vega-s9x.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-vega-s9x.mod
