cmd_drivers/dax/kmem.mod := printf '%s\n'   kmem.o | awk '!x[$$0]++ { print("drivers/dax/"$$0) }' > drivers/dax/kmem.mod
