cmd_drivers/input/misc/hisi_powerkey.mod := printf '%s\n'   hisi_powerkey.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/hisi_powerkey.mod
