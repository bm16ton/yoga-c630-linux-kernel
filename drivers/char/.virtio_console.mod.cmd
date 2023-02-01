cmd_drivers/char/virtio_console.mod := printf '%s\n'   virtio_console.o | awk '!x[$$0]++ { print("drivers/char/"$$0) }' > drivers/char/virtio_console.mod
