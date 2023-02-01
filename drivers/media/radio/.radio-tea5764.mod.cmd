cmd_drivers/media/radio/radio-tea5764.mod := printf '%s\n'   radio-tea5764.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/radio-tea5764.mod
