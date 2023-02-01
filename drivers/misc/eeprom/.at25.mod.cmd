cmd_drivers/misc/eeprom/at25.mod := printf '%s\n'   at25.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/at25.mod
