cmd_drivers/media/radio/radio-raremono.mod := printf '%s\n'   radio-raremono.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-raremono.mod
