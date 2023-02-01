cmd_drivers/pps/clients/pps-ldisc.mod := printf '%s\n'   pps-ldisc.o | awk '!x[$$0]++ { print("drivers/pps/clients/"$$0) }' > drivers/pps/clients/pps-ldisc.mod
