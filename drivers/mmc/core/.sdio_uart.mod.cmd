cmd_drivers/mmc/core/sdio_uart.mod := printf '%s\n'   sdio_uart.o | awk '!x[$$0]++ { print("drivers/mmc/core/"$$0) }' > drivers/mmc/core/sdio_uart.mod
