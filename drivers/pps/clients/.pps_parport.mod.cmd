cmd_drivers/pps/clients/pps_parport.mod := printf '%s\n'   pps_parport.o | awk '!x[$$0]++ { print("drivers/pps/clients/"$$0) }' > drivers/pps/clients/pps_parport.mod
