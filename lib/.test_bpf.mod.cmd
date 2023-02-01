cmd_lib/test_bpf.mod := printf '%s\n'   test_bpf.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_bpf.mod
