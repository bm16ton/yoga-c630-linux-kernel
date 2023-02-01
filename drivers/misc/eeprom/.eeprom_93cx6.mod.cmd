cmd_drivers/misc/eeprom/eeprom_93cx6.mod := printf '%s\n'   eeprom_93cx6.o | awk '!x[$$0]++ { print("drivers/misc/eeprom/"$$0) }' > drivers/misc/eeprom/eeprom_93cx6.mod
