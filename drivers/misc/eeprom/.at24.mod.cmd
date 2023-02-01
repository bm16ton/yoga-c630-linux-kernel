cmd_drivers/misc/eeprom/at24.mod := printf '%s\n'   at24.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/at24.mod
