cmd_drivers/watchdog/wdat_wdt.mod := printf '%s\n'   wdat_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/wdat_wdt.mod
