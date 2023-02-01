cmd_drivers/dax/dax.mod := printf '%s\n'   super.o bus.o | awk '!x[$$0]++ { print("drivers/dax/"$$0) }' > drivers/dax/dax.mod
