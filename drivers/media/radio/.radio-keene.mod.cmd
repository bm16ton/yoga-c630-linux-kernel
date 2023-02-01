cmd_drivers/media/radio/radio-keene.mod := printf '%s\n'   radio-keene.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-keene.mod
