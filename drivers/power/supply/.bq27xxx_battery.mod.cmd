cmd_drivers/power/supply/bq27xxx_battery.mod := printf '%s\n'   bq27xxx_battery.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/bq27xxx_battery.mod
