cmd_drivers/gnss/gnss-sirf.mod := printf '%s\n'   sirf.o | awk '!x[$$0]++ { print("drivers/gnss/"$$0) }' > drivers/gnss/gnss-sirf.mod
