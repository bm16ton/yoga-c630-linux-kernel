cmd_drivers/char/hw_random/meson-rng.mod := printf '%s\n'   meson-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/meson-rng.mod
