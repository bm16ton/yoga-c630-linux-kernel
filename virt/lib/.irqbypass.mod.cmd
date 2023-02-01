cmd_virt/lib/irqbypass.mod := printf '%s\n'   irqbypass.o | awk '!x[$$0]++ { print("virt/lib/"$$0) }' > virt/lib/irqbypass.mod
