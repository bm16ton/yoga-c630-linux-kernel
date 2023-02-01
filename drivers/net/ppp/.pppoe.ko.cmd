cmd_drivers/net/ppp/pppoe.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/ppp/pppoe.ko drivers/net/ppp/pppoe.o drivers/net/ppp/pppoe.mod.o;  true
