cmd_drivers/mfd/lpc_sch.mod := printf '%s\n'   lpc_sch.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/lpc_sch.mod
