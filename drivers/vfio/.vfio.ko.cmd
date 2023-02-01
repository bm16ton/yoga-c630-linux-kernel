cmd_drivers/vfio/vfio.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/vfio/vfio.ko drivers/vfio/vfio.o drivers/vfio/vfio.mod.o;  true
