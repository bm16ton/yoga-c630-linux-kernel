cmd_drivers/dma/sun6i-dma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/sun6i-dma.ko drivers/dma/sun6i-dma.o drivers/dma/sun6i-dma.mod.o;  true
