cmd_drivers/media/rc/ir-sharp-decoder.mod := printf '%s\n'   ir-sharp-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-sharp-decoder.mod
