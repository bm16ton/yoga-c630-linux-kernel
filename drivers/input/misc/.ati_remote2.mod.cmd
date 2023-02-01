cmd_drivers/input/misc/ati_remote2.mod := printf '%s\n'   ati_remote2.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/ati_remote2.mod
