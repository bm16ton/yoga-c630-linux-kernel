cmd_drivers/power/supply/sbs-battery.mod := printf '%s\n'   sbs-battery.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/sbs-battery.mod
