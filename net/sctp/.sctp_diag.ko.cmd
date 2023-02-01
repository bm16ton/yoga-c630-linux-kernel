cmd_net/sctp/sctp_diag.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/sctp/sctp_diag.ko net/sctp/sctp_diag.o net/sctp/sctp_diag.mod.o;  true
