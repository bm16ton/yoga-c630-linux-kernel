cmd_drivers/net/hamradio/baycom_par.mod := printf '%s\n'   baycom_par.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/baycom_par.mod
