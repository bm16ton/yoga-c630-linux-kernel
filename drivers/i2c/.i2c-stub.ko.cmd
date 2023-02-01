cmd_drivers/i2c/i2c-stub.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/i2c/i2c-stub.ko drivers/i2c/i2c-stub.o drivers/i2c/i2c-stub.mod.o;  true
