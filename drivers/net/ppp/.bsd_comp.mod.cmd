cmd_drivers/net/ppp/bsd_comp.mod := printf '%s\n'   bsd_comp.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/bsd_comp.mod
