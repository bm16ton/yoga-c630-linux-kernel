cmd_net/unix/unix_diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/unix/unix_diag.ko net/unix/unix_diag.o net/unix/unix_diag.mod.o;  true
