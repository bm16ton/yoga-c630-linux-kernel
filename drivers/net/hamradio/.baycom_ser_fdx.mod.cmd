cmd_drivers/net/hamradio/baycom_ser_fdx.mod := printf '%s\n'   baycom_ser_fdx.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/baycom_ser_fdx.mod
