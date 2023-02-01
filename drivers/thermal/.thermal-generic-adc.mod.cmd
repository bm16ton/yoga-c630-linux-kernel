cmd_drivers/thermal/thermal-generic-adc.mod := printf '%s\n'   thermal-generic-adc.o | awk '!x[$$0]++ { print("drivers/thermal/"$$0) }' > drivers/thermal/thermal-generic-adc.mod
