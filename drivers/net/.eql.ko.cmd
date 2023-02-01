cmd_drivers/net/eql.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/eql.ko drivers/net/eql.o drivers/net/eql.mod.o;  true
