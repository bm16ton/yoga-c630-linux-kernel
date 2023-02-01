cmd_drivers/crypto/cavium/cpt/cptpf.mod := printf '%s\n'   cptpf_main.o cptpf_mbox.o | awk '!x[$$0]++ { print("drivers/crypto/cavium/cpt/"$$0) }' > drivers/crypto/cavium/cpt/cptpf.mod
