cmd_drivers/power/supply/gpio-charger.mod := printf '%s\n'   gpio-charger.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/gpio-charger.mod
