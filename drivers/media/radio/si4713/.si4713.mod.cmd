cmd_drivers/media/radio/si4713/si4713.mod := printf '%s\n'   si4713.o | awk '!x[$$0]++ { print("drivers/media/radio/si4713/"$$0) }' > drivers/media/radio/si4713/si4713.mod
