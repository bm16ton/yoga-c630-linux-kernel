cmd_drivers/spi/spi-xlp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/spi/spi-xlp.ko drivers/spi/spi-xlp.o drivers/spi/spi-xlp.mod.o;  true
