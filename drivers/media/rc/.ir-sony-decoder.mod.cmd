cmd_drivers/media/rc/ir-sony-decoder.mod := printf '%s\n'   ir-sony-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-sony-decoder.mod
