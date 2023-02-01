cmd_lib/reed_solomon/reed_solomon.mod := printf '%s\n'   reed_solomon.o | awk '!x[$$0]++ { print("lib/reed_solomon/"$$0) }' > lib/reed_solomon/reed_solomon.mod
