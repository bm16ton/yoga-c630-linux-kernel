cmd_drivers/acpi/acpi_ipmi.mod := printf '%s\n'   acpi_ipmi.o | awk '!x[$$0]++ { print("drivers/acpi/"$$0) }' > drivers/acpi/acpi_ipmi.mod
