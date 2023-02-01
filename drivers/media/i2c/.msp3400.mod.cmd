cmd_drivers/media/i2c/msp3400.mod := printf '%s\n'   msp3400-driver.o msp3400-kthreads.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/msp3400.mod
