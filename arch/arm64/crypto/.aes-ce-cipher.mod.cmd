cmd_arch/arm64/crypto/aes-ce-cipher.mod := printf '%s\n'   aes-ce-core.o aes-ce-glue.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/aes-ce-cipher.mod
