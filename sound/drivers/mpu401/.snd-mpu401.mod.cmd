cmd_sound/drivers/mpu401/snd-mpu401.mod := printf '%s\n'   mpu401.o | awk '!x[$$0]++ { print("sound/drivers/mpu401/"$$0) }' > sound/drivers/mpu401/snd-mpu401.mod
