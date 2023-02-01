cmd_drivers/power/supply/yoga-c630-ec.mod := printf '%s\n'   yoga-c630-ec.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/yoga-c630-ec.mod
