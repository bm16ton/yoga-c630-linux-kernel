cmd_vmlinux.o := ld  -EL  -maarch64elf -z noexecstack  -r -o vmlinux.o  --whole-archive vmlinux.a --no-whole-archive --start-group ./drivers/firmware/efi/libstub/lib.a --end-group 
