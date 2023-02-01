cmd_net/xfrm/modules.order := {   echo net/xfrm/xfrm_algo.ko;   echo net/xfrm/xfrm_user.ko;   echo net/xfrm/xfrm_ipcomp.ko;   echo net/xfrm/xfrm_interface.ko; :; } > net/xfrm/modules.order
