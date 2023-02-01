cmd_drivers/gnss/gnss.mod := printf '%s\n'   core.o | awk '!x[$$0]++ { print("drivers/gnss/"$$0) }' > drivers/gnss/gnss.mod
