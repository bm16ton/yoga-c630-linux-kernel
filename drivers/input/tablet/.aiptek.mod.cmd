cmd_drivers/input/tablet/aiptek.mod := printf '%s\n'   aiptek.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/aiptek.mod
