cmd_drivers/fpga/fpga-mgr.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/fpga/fpga-mgr.ko drivers/fpga/fpga-mgr.o drivers/fpga/fpga-mgr.mod.o;  true
