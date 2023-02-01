cmd_drivers/thermal/rockchip_thermal.mod := printf '%s\n'   rockchip_thermal.o | awk '!x[$$0]++ { print("drivers/thermal/"$$0) }' > drivers/thermal/rockchip_thermal.mod
