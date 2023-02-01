cmd_drivers/leds/leds-pca963x.mod := printf '%s\n'   leds-pca963x.o | awk '!x[$$0]++ { print("drivers/leds/"$$0) }' > drivers/leds/leds-pca963x.mod
