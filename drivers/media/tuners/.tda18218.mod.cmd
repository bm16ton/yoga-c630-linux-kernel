cmd_drivers/media/tuners/tda18218.mod := printf '%s\n'   tda18218.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/tda18218.mod
