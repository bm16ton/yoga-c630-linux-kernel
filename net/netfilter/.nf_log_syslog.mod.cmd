cmd_net/netfilter/nf_log_syslog.mod := printf '%s\n'   nf_log_syslog.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/nf_log_syslog.mod
