cmd_drivers/media/rc/ir-spi.mod := printf '%s\n'   ir-spi.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-spi.mod
