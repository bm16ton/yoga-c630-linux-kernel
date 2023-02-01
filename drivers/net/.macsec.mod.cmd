cmd_drivers/net/macsec.mod := printf '%s\n'   macsec.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/macsec.mod
