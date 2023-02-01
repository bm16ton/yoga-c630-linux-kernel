cmd_drivers/misc/lis3lv02d/lis3lv02d_i2c.mod := printf '%s\n'   lis3lv02d_i2c.o | awk '!x[$$0]++ { print("drivers/misc/lis3lv02d/"$$0) }' > drivers/misc/lis3lv02d/lis3lv02d_i2c.mod
