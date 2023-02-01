cmd_drivers/net/ppp/pppox.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/ppp/pppox.ko drivers/net/ppp/pppox.o drivers/net/ppp/pppox.mod.o;  true
