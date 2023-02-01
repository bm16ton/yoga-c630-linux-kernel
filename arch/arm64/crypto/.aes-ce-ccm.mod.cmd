cmd_arch/arm64/crypto/aes-ce-ccm.mod := printf '%s\n'   aes-ce-ccm-glue.o aes-ce-ccm-core.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/aes-ce-ccm.mod
