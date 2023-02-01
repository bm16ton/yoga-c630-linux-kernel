cmd_drivers/net/can/spi/mcp251x.mod := printf '%s\n'   mcp251x.o | awk '!x[$$0]++ { print("drivers/net/can/spi/"$$0) }' > drivers/net/can/spi/mcp251x.mod
