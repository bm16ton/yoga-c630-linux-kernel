cmd_drivers/iio/adc/meson_saradc.mod := printf '%s\n'   meson_saradc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/meson_saradc.mod
