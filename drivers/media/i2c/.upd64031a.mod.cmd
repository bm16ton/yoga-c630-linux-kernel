cmd_drivers/media/i2c/upd64031a.mod := printf '%s\n'   upd64031a.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/upd64031a.mod
