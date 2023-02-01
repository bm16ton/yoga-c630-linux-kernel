cmd_drivers/dax/dax_pmem.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dax/dax_pmem.ko drivers/dax/dax_pmem.o drivers/dax/dax_pmem.mod.o;  true
