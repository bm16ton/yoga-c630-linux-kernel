cmd_drivers/watchdog/gpio_wdt.mod := printf '%s\n'   gpio_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/gpio_wdt.mod
