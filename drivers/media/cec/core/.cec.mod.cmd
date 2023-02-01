cmd_drivers/media/cec/core/cec.mod := printf '%s\n'   cec-core.o cec-adap.o cec-api.o | awk '!x[$$0]++ { print("drivers/media/cec/core/"$$0) }' > drivers/media/cec/core/cec.mod
