cmd_drivers/media/radio/shark2.mod := printf '%s\n'   radio-shark2.o radio-tea5777.o | awk '!x[$$0]++ { print("drivers/media/radio/"$$0) }' > drivers/media/radio/shark2.mod
