cmd_drivers/vhost/vhost.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/vhost/vhost.ko drivers/vhost/vhost.o drivers/vhost/vhost.mod.o;  true
