cmd_drivers/media/radio/radio-shark.mod := printf '%s\n'   radio-shark.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-shark.mod
