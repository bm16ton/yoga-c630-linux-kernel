cmd_drivers/media/i2c/upd64083.mod := printf '%s\n'   upd64083.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/upd64083.mod
