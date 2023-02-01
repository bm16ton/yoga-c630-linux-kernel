cmd_drivers/input/touchscreen/wacom_w8001.mod := printf '%s\n'   wacom_w8001.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/wacom_w8001.mod
