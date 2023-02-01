cmd_drivers/media/radio/radio-mr800.mod := printf '%s\n'   radio-mr800.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-mr800.mod
