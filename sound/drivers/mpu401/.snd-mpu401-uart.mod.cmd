cmd_sound/drivers/mpu401/snd-mpu401-uart.mod := printf '%s\n'   mpu401_uart.o | awk '!x[$$0]++ { print("sound/drivers/mpu401/"$$0) }' > sound/drivers/mpu401/snd-mpu401-uart.mod
