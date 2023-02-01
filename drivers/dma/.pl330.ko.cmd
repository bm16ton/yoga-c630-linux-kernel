cmd_drivers/dma/pl330.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/pl330.ko drivers/dma/pl330.o drivers/dma/pl330.mod.o;  true
