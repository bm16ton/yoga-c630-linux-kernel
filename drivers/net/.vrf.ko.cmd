cmd_drivers/net/vrf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/vrf.ko drivers/net/vrf.o drivers/net/vrf.mod.o;  true
