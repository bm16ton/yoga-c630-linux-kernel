cmd_drivers/thermal/sun8i_thermal.mod := printf '%s\n'   sun8i_thermal.o | awk '!x[$$0]++ { print("drivers/thermal/"$$0) }' > drivers/thermal/sun8i_thermal.mod
