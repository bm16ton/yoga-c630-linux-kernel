cmd_drivers/net/mdio/acpi_mdio.mod := printf '%s\n'   acpi_mdio.o | awk '!x[$$0]++ { print("drivers/net/mdio/"$$0) }' > drivers/net/mdio/acpi_mdio.mod
