cmd_drivers/net/ppp/pptp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/ppp/pptp.ko drivers/net/ppp/pptp.o drivers/net/ppp/pptp.mod.o;  true
