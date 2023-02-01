cmd_drivers/char/hw_random/optee-rng.mod := printf '%s\n'   optee-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/optee-rng.mod
