cmd_drivers/input/touchscreen/fujitsu_ts.mod := printf '%s\n'   fujitsu_ts.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/fujitsu_ts.mod
