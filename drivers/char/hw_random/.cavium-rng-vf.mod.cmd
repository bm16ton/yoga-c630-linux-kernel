cmd_drivers/char/hw_random/cavium-rng-vf.mod := printf '%s\n'   cavium-rng-vf.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/cavium-rng-vf.mod
