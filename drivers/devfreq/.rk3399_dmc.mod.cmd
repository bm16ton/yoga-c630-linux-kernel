cmd_drivers/devfreq/rk3399_dmc.mod := printf '%s\n'   rk3399_dmc.o | awk '!x[$$0]++ { print("drivers/devfreq/"$$0) }' > drivers/devfreq/rk3399_dmc.mod
