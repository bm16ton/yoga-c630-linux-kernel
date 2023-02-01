cmd_drivers/gpio/gpio-virtio.mod := printf '%s\n'   gpio-virtio.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-virtio.mod
