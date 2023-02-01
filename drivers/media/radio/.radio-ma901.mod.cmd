cmd_drivers/media/radio/radio-ma901.mod := printf '%s\n'   radio-ma901.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-ma901.mod
