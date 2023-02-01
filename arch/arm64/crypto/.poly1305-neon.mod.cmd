cmd_arch/arm64/crypto/poly1305-neon.mod := printf '%s\n'   poly1305-core.o poly1305-glue.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/poly1305-neon.mod
