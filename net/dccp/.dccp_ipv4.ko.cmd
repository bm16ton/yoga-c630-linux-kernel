cmd_net/dccp/dccp_ipv4.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dccp/dccp_ipv4.ko net/dccp/dccp_ipv4.o net/dccp/dccp_ipv4.mod.o;  true
