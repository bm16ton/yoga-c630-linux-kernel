cmd_drivers/misc/eeprom/ee1004.mod := printf '%s\n'   ee1004.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/ee1004.mod
