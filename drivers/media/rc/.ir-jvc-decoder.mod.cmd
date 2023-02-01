cmd_drivers/media/rc/ir-jvc-decoder.mod := printf '%s\n'   ir-jvc-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-jvc-decoder.mod
