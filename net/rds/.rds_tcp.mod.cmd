cmd_net/rds/rds_tcp.mod := printf '%s\n'   tcp.o tcp_connect.o tcp_listen.o tcp_recv.o tcp_send.o tcp_stats.o | awk '!x[$$0]++ { print("net/rds/"$$0) }' > net/rds/rds_tcp.mod
