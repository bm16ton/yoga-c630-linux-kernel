cmd_drivers/spi/spi-qup.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/spi/spi-qup.ko drivers/spi/spi-qup.o drivers/spi/spi-qup.mod.o;  true
