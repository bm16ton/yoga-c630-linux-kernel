cmd_drivers/scsi/bfa/bfa.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/bfa/bfa.ko drivers/scsi/bfa/bfa.o drivers/scsi/bfa/bfa.mod.o;  true
