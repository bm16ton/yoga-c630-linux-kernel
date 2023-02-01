cmd_drivers/spi/spidev.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/spi/spidev.ko drivers/spi/spidev.o drivers/spi/spidev.mod.o;  true
