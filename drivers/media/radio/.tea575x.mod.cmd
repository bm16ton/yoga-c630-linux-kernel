cmd_drivers/media/radio/tea575x.mod := printf '%s\n'   tea575x.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/tea575x.mod
