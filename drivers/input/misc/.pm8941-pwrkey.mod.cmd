cmd_drivers/input/misc/pm8941-pwrkey.mod := printf '%s\n'   pm8941-pwrkey.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/pm8941-pwrkey.mod
