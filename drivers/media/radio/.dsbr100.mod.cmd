cmd_drivers/media/radio/dsbr100.mod := printf '%s\n'   dsbr100.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/dsbr100.mod
