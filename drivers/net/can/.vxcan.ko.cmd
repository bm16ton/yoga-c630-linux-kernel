cmd_drivers/net/can/vxcan.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/can/vxcan.ko drivers/net/can/vxcan.o drivers/net/can/vxcan.mod.o;  true
