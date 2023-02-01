cmd_drivers/media/rc/ir-rc6-decoder.mod := printf '%s\n'   ir-rc6-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-rc6-decoder.mod
