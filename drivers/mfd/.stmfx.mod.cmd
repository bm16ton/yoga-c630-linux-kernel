cmd_drivers/mfd/stmfx.mod := printf '%s\n'   stmfx.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/stmfx.mod
