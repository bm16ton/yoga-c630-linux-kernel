cmd_drivers/scsi/st.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/st.ko drivers/scsi/st.o drivers/scsi/st.mod.o;  true
