cmd_block/kyber-iosched.mod := printf '%s\n'   kyber-iosched.o | awk '!x[$$0]++ { print("block/"$$0) }' > block/kyber-iosched.mod
