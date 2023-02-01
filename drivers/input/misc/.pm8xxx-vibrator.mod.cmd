cmd_drivers/input/misc/pm8xxx-vibrator.mod := printf '%s\n'   pm8xxx-vibrator.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/pm8xxx-vibrator.mod
