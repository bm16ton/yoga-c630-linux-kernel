cmd_drivers/watchdog/sunxi_wdt.mod := printf '%s\n'   sunxi_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/sunxi_wdt.mod
