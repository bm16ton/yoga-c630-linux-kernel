cmd_drivers/media/radio/radio-maxiradio.mod := printf '%s\n'   radio-maxiradio.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-maxiradio.mod
