cmd_drivers/media/tuners/tda18212.mod := printf '%s\n'   tda18212.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda18212.mod
