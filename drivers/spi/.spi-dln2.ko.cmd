cmd_drivers/spi/spi-dln2.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/spi/spi-dln2.ko drivers/spi/spi-dln2.o drivers/spi/spi-dln2.mod.o;  true
