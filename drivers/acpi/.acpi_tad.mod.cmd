cmd_drivers/acpi/acpi_tad.mod := printf '%s\n'   acpi_tad.o | awk '!x[$$0]++ { print("drivers/acpi/"$$0) }' > drivers/acpi/acpi_tad.mod
