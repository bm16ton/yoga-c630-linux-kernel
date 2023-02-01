cmd_drivers/acpi/apei/built-in.a := rm -f drivers/acpi/apei/built-in.a;  printf "drivers/acpi/apei/%s " apei-base.o hest.o erst.o bert.o ghes.o | xargs ar cDPrST drivers/acpi/apei/built-in.a
