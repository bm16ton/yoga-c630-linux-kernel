cmd_lib/crypto/built-in.a := rm -f lib/crypto/built-in.a;  printf "lib/crypto/%s " memneq.o utils.o chacha.o aes.o blake2s.o blake2s-generic.o sha1.o sha256.o | xargs ar cDPrST lib/crypto/built-in.a
