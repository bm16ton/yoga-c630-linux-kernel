cmd_drivers/leds/rgb/leds-qcom-lpg.mod := printf '%s\n'   leds-qcom-lpg.o | awk '!x[$$0]++ { print("drivers/leds/rgb/"$$0) }' > drivers/leds/rgb/leds-qcom-lpg.mod
