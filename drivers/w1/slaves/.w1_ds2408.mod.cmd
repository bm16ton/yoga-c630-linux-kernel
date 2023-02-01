cmd_drivers/w1/slaves/w1_ds2408.mod := printf '%s\n'   w1_ds2408.o | awk '!x[$$0]++ { print("drivers/w1/slaves/"$$0) }' > drivers/w1/slaves/w1_ds2408.mod
