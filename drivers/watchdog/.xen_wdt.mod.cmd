cmd_drivers/watchdog/xen_wdt.mod := printf '%s\n'   xen_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/xen_wdt.mod
