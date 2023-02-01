cmd_drivers/net/can/m_can/m_can.mod := printf '%s\n'   m_can.o | awk '!x[$$0]++ { print("drivers/net/can/m_can/"$$0) }' > drivers/net/can/m_can/m_can.mod
