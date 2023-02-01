cmd_drivers/watchdog/qcom-wdt.mod := printf '%s\n'   qcom-wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/qcom-wdt.mod
