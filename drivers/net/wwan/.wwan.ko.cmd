cmd_drivers/net/wwan/wwan.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/wwan/wwan.ko drivers/net/wwan/wwan.o drivers/net/wwan/wwan.mod.o;  true
