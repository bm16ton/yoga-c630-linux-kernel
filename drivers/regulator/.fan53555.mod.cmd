cmd_drivers/regulator/fan53555.mod := printf '%s\n'   fan53555.o | awk '!x[$$0]++ { print("drivers/regulator/"$$0) }' > drivers/regulator/fan53555.mod
