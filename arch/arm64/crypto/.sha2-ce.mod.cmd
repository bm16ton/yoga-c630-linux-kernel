cmd_arch/arm64/crypto/sha2-ce.mod := printf '%s\n'   sha2-ce-glue.o sha2-ce-core.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/sha2-ce.mod
