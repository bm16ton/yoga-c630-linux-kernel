cmd_drivers/media/mmc/siano/smssdio.mod := printf '%s\n'   smssdio.o | awk '!x[$$0]++ { print("drivers/media/mmc/siano/"$$0) }' > drivers/media/mmc/siano/smssdio.mod
