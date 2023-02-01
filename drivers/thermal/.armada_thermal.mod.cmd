cmd_drivers/thermal/armada_thermal.mod := printf '%s\n'   armada_thermal.o | awk '!x[$$0]++ { print("drivers/thermal/"$$0) }' > drivers/thermal/armada_thermal.mod
