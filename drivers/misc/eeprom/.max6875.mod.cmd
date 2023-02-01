cmd_drivers/misc/eeprom/max6875.mod := printf '%s\n'   max6875.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/max6875.mod
