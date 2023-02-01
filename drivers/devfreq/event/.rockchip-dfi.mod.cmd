cmd_drivers/devfreq/event/rockchip-dfi.mod := printf '%s\n'   rockchip-dfi.o | awk '!x[$$0]++ { print("drivers/devfreq/event/"$$0) }' > drivers/devfreq/event/rockchip-dfi.mod
