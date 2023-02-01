cmd_drivers/char/hw_random/virtio-rng.mod := printf '%s\n'   virtio-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/virtio-rng.mod
