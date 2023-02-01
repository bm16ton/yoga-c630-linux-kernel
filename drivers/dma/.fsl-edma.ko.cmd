cmd_drivers/dma/fsl-edma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/fsl-edma.ko drivers/dma/fsl-edma.o drivers/dma/fsl-edma.mod.o;  true
