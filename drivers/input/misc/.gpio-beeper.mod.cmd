cmd_drivers/input/misc/gpio-beeper.mod := printf '%s\n'   gpio-beeper.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/gpio-beeper.mod
