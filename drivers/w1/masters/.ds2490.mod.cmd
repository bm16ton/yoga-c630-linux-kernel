cmd_drivers/w1/masters/ds2490.mod := printf '%s\n'   ds2490.o | awk '!x[$$0]++ { print("drivers/w1/masters/"$$0) }' > drivers/w1/masters/ds2490.mod
