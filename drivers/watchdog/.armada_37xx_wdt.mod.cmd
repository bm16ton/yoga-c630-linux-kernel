cmd_drivers/watchdog/armada_37xx_wdt.mod := printf '%s\n'   armada_37xx_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/armada_37xx_wdt.mod
