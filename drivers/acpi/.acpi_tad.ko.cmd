cmd_drivers/acpi/acpi_tad.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/acpi/acpi_tad.ko drivers/acpi/acpi_tad.o drivers/acpi/acpi_tad.mod.o;  true
