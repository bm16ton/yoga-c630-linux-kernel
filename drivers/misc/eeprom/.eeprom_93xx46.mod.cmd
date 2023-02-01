cmd_drivers/misc/eeprom/eeprom_93xx46.mod := printf '%s\n'   eeprom_93xx46.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/eeprom_93xx46.mod
