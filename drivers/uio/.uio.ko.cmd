cmd_drivers/uio/uio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/uio/uio.ko drivers/uio/uio.o drivers/uio/uio.mod.o;  true
