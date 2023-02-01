cmd_drivers/watchdog/sbsa_gwdt.mod := printf '%s\n'   sbsa_gwdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/sbsa_gwdt.mod
