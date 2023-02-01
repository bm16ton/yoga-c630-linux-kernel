cmd_drivers/input/tablet/acecad.mod := printf '%s\n'   acecad.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/acecad.mod
