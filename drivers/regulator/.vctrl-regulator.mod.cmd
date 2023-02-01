cmd_drivers/regulator/vctrl-regulator.mod := printf '%s\n'   vctrl-regulator.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/vctrl-regulator.mod
