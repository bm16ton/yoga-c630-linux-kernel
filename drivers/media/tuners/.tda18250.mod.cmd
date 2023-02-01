cmd_drivers/media/tuners/tda18250.mod := printf '%s\n'   tda18250.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda18250.mod
