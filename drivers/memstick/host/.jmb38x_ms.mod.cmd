cmd_drivers/memstick/host/jmb38x_ms.mod := printf '%s\n'   jmb38x_ms.o | awk '!x[$$0]++ { print("drivers/memstick/host/"$$0) }' > drivers/memstick/host/jmb38x_ms.mod
