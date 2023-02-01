cmd_drivers/media/rc/pwm-ir-tx.mod := printf '%s\n'   pwm-ir-tx.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/pwm-ir-tx.mod
