cmd_net/dns_resolver/dns_resolver.mod := printf '%s\n'   dns_key.o dns_query.o | awk '!x[$$0]++ { print("net/dns_resolver/"$$0) }' > net/dns_resolver/dns_resolver.mod
