cmd_drivers/media/radio/tef6862.mod := printf '%s\n'   tef6862.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/tef6862.mod
