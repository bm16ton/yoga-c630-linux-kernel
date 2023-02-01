cmd_drivers/net/can/grcan.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/can/grcan.ko drivers/net/can/grcan.o drivers/net/can/grcan.mod.o;  true
