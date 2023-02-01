cmd_drivers/power/supply/cw2015_battery.mod := printf '%s\n'   cw2015_battery.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/cw2015_battery.mod
