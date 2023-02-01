cmd_drivers/w1/masters/ds2482.mod := printf '%s\n'   ds2482.o | awk '!x[$$0]++ { print("drivers/w1/masters/"$$0) }' > drivers/w1/masters/ds2482.mod
