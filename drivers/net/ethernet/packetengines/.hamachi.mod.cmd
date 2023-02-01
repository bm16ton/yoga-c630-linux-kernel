cmd_drivers/net/ethernet/packetengines/hamachi.mod := printf '%s\n'   hamachi.o | awk '!x[$$0]++ { print("drivers/net/ethernet/packetengines/"$$0) }' > drivers/net/ethernet/packetengines/hamachi.mod
