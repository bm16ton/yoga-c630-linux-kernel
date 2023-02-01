cmd_net/appletalk/appletalk.mod := printf '%s\n'   aarp.o ddp.o dev.o atalk_proc.o sysctl_net_atalk.o | awk '!x[$$0]++ { print("net/appletalk/"$$0) }' > net/appletalk/appletalk.mod
