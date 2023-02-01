cmd_drivers/hwmon/npcm750-pwm-fan.mod := printf '%s\n'   npcm750-pwm-fan.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/npcm750-pwm-fan.mod
