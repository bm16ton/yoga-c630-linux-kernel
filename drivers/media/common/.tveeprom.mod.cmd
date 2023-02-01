cmd_drivers/media/common/tveeprom.mod := printf '%s\n'   tveeprom.o | awk '!x[$$0]++ { print("drivers/media/common/"$$0) }' > drivers/media/common/tveeprom.mod
