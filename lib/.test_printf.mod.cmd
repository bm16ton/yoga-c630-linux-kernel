cmd_lib/test_printf.mod := printf '%s\n'   test_printf.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_printf.mod
