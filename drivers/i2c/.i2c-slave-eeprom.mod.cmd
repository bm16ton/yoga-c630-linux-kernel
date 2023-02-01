cmd_drivers/i2c/i2c-slave-eeprom.mod := printf '%s\n'   i2c-slave-eeprom.o | awk '!x[$$0]++ { print("drivers/i2c/"$$0) }' > drivers/i2c/i2c-slave-eeprom.mod
