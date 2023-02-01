cmd_drivers/char/hw_random/rng-core.mod := printf '%s\n'   core.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/rng-core.mod
