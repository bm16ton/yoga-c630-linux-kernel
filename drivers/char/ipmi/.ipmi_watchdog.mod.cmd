cmd_drivers/char/ipmi/ipmi_watchdog.mod := printf '%s\n'   ipmi_watchdog.o | awk '!x[$$0]++ { print("drivers/char/ipmi/"$$0) }' > drivers/char/ipmi/ipmi_watchdog.mod
