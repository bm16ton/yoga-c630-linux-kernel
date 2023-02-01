cmd_drivers/media/radio/saa7706h.mod := printf '%s\n'   saa7706h.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/saa7706h.mod
