cmd_drivers/input/serio/altera_ps2.mod := printf '%s\n'   altera_ps2.o | awk '!x[$$0]++ { print("drivers/input/serio/"$$0) }' > drivers/input/serio/altera_ps2.mod
