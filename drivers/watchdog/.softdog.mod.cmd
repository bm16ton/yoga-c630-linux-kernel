cmd_drivers/watchdog/softdog.mod := printf '%s\n'   softdog.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/softdog.mod
