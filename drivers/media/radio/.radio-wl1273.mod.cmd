cmd_drivers/media/radio/radio-wl1273.mod := printf '%s\n'   radio-wl1273.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-wl1273.mod
