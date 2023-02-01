cmd_lib/test_static_keys.mod := printf '%s\n'   test_static_keys.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_static_keys.mod
