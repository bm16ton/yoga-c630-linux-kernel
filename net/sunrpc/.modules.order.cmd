cmd_net/sunrpc/modules.order := {   echo net/sunrpc/sunrpc.ko;   cat net/sunrpc/auth_gss/modules.order;   cat net/sunrpc/xprtrdma/modules.order; :; } > net/sunrpc/modules.order
