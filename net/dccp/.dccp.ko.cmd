cmd_net/dccp/dccp.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dccp/dccp.ko net/dccp/dccp.o net/dccp/dccp.mod.o;  true
