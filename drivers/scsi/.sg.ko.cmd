cmd_drivers/scsi/sg.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/sg.ko drivers/scsi/sg.o drivers/scsi/sg.mod.o;  true
