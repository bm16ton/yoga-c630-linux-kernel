cmd_drivers/crypto/qce/qcrypto.mod := printf '%s\n'   core.o common.o dma.o sha.o skcipher.o aead.o | awk '!x[$$0]++ { print("drivers/crypto/qce/"$$0) }' > drivers/crypto/qce/qcrypto.mod
