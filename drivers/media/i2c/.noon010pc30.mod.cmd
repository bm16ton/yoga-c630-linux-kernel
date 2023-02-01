cmd_drivers/media/i2c/noon010pc30.mod := printf '%s\n'   noon010pc30.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/noon010pc30.mod
