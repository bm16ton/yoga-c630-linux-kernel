cmd_drivers/mfd/ti_am335x_tscadc.mod := printf '%s\n'   ti_am335x_tscadc.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/ti_am335x_tscadc.mod
