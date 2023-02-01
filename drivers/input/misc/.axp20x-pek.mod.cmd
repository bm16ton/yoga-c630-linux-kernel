cmd_drivers/input/misc/axp20x-pek.mod := printf '%s\n'   axp20x-pek.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/axp20x-pek.mod
