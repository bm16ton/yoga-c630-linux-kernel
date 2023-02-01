cmd_drivers/dma/qcom/hdma.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/dma/qcom/hdma.ko drivers/dma/qcom/hdma.o drivers/dma/qcom/hdma.mod.o;  true
