cmd_drivers/dma/k3dma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/k3dma.ko drivers/dma/k3dma.o drivers/dma/k3dma.mod.o;  true
