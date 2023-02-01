cmd_drivers/thermal/hisi_thermal.mod := printf '%s\n'   hisi_thermal.o | awk '!x[$$0]++ { print("drivers/thermal/"$$0) }' > drivers/thermal/hisi_thermal.mod
