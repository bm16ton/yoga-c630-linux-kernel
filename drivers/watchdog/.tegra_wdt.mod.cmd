cmd_drivers/watchdog/tegra_wdt.mod := printf '%s\n'   tegra_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/tegra_wdt.mod
