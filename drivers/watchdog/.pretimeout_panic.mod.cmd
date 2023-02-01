cmd_drivers/watchdog/pretimeout_panic.mod := printf '%s\n'   pretimeout_panic.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/pretimeout_panic.mod
