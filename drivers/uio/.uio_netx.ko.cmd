cmd_drivers/uio/uio_netx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/uio/uio_netx.ko drivers/uio/uio_netx.o drivers/uio/uio_netx.mod.o;  true
