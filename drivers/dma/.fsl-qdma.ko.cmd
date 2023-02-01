cmd_drivers/dma/fsl-qdma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/fsl-qdma.ko drivers/dma/fsl-qdma.o drivers/dma/fsl-qdma.mod.o;  true
