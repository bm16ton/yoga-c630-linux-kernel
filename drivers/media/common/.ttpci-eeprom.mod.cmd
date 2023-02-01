cmd_drivers/media/common/ttpci-eeprom.mod := printf '%s\n'   ttpci-eeprom.o | awk '!x[$$0]++ { print("drivers/media/common/"$$0) }' > drivers/media/common/ttpci-eeprom.mod
