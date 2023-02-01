cmd_drivers/misc/eeprom/eeprom.mod := printf '%s\n'   eeprom.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/eeprom.mod
