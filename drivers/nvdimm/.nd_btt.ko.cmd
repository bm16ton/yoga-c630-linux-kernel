cmd_drivers/nvdimm/nd_btt.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/nvdimm/nd_btt.ko drivers/nvdimm/nd_btt.o drivers/nvdimm/nd_btt.mod.o;  true
