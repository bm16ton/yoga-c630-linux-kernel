cmd_arch/arm64/crypto/aes-ce-blk.mod := printf '%s\n'   aes-glue-ce.o aes-ce.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/aes-ce-blk.mod
