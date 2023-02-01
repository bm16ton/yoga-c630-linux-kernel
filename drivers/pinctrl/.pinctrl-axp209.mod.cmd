cmd_drivers/pinctrl/pinctrl-axp209.mod := printf '%s\n'   pinctrl-axp209.o | awk '!x[$$0]++ { print("drivers/pinctrl/"$$0) }' > drivers/pinctrl/pinctrl-axp209.mod
