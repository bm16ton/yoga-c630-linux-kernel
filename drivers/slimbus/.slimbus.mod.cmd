cmd_drivers/slimbus/slimbus.mod := printf '%s\n'   core.o messaging.o sched.o stream.o | awk '!x[$$0]++ { print("drivers/slimbus/"$$0) }' > drivers/slimbus/slimbus.mod
