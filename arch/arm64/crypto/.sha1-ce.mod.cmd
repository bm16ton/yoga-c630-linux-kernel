cmd_arch/arm64/crypto/sha1-ce.mod := printf '%s\n'   sha1-ce-glue.o sha1-ce-core.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/sha1-ce.mod
