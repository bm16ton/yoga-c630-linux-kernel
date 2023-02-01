cmd_arch/arm64/crypto/ghash-ce.mod := printf '%s\n'   ghash-ce-glue.o ghash-ce-core.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/ghash-ce.mod
