cmd_drivers/watchdog/sp805_wdt.mod := printf '%s\n'   sp805_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/sp805_wdt.mod
