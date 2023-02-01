cmd_drivers/watchdog/dw_wdt.mod := printf '%s\n'   dw_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/dw_wdt.mod
