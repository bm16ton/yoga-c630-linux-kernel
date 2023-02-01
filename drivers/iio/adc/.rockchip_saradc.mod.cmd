cmd_drivers/iio/adc/rockchip_saradc.mod := printf '%s\n'   rockchip_saradc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/rockchip_saradc.mod
