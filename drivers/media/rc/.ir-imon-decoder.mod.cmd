cmd_drivers/media/rc/ir-imon-decoder.mod := printf '%s\n'   ir-imon-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-imon-decoder.mod
