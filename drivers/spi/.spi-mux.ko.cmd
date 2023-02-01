cmd_drivers/spi/spi-mux.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/spi/spi-mux.ko drivers/spi/spi-mux.o drivers/spi/spi-mux.mod.o;  true
