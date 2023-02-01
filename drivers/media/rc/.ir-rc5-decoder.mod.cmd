cmd_drivers/media/rc/ir-rc5-decoder.mod := printf '%s\n'   ir-rc5-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-rc5-decoder.mod
