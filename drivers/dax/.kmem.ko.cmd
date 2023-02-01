cmd_drivers/dax/kmem.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dax/kmem.ko drivers/dax/kmem.o drivers/dax/kmem.mod.o;  true
