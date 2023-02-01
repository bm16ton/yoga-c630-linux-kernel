cmd_lib/test_static_key_base.mod := printf '%s\n'   test_static_key_base.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_static_key_base.mod
