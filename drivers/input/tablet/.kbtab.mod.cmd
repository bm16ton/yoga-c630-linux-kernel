cmd_drivers/input/tablet/kbtab.mod := printf '%s\n'   kbtab.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/kbtab.mod
