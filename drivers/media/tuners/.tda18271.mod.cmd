cmd_drivers/media/tuners/tda18271.mod := printf '%s\n'   tda18271-maps.o tda18271-common.o tda18271-fe.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda18271.mod
