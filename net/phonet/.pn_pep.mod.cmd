cmd_net/phonet/pn_pep.mod := printf '%s\n'   pep.o pep-gprs.o | awk '!x[$$0]++ { print("net/phonet/"$$0) }' > net/phonet/pn_pep.mod
