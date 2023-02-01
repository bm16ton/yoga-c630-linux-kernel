cmd_drivers/input/touchscreen/goodix_ts.mod := printf '%s\n'   goodix.o goodix_fwupload.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/goodix_ts.mod
