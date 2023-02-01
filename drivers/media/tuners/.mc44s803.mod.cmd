cmd_drivers/media/tuners/mc44s803.mod := printf '%s\n'   mc44s803.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/mc44s803.mod
