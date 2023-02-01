cmd_drivers/acpi/nfit/nfit.mod := printf '%s\n'   core.o intel.o | awk '!x[$$0]++ { print("drivers/acpi/nfit/"$$0) }' > drivers/acpi/nfit/nfit.mod
