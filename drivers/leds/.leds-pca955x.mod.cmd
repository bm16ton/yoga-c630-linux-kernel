cmd_drivers/leds/leds-pca955x.mod := printf '%s\n'   leds-pca955x.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-pca955x.mod
