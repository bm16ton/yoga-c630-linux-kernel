cmd_drivers/iio/light/acpi-als.mod := printf '%s\n'   acpi-als.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/acpi-als.mod
