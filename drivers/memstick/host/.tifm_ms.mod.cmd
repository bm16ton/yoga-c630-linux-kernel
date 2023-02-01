cmd_drivers/memstick/host/tifm_ms.mod := printf '%s\n'   tifm_ms.o | awk '!x[$$0]++ { print("drivers/memstick/host/"$$0) }' > drivers/memstick/host/tifm_ms.mod
