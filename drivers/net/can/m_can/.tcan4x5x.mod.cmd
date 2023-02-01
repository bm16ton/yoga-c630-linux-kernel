cmd_drivers/net/can/m_can/tcan4x5x.mod := printf '%s\n'   tcan4x5x-core.o tcan4x5x-regmap.o | awk '!x[$$0]++ { print("drivers/net/can/m_can/"$$0) }' > drivers/net/can/m_can/tcan4x5x.mod
