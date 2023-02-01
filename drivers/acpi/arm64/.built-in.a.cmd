cmd_drivers/acpi/arm64/built-in.a := rm -f drivers/acpi/arm64/built-in.a;  printf "drivers/acpi/arm64/%s " iort.o gtdt.o dma.o | xargs ar cDPrST drivers/acpi/arm64/built-in.a
