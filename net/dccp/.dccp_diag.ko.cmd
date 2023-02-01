cmd_net/dccp/dccp_diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dccp/dccp_diag.ko net/dccp/dccp_diag.o net/dccp/dccp_diag.mod.o;  true
