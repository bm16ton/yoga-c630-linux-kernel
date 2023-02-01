cmd_net/ieee802154/modules.order := {   cat net/ieee802154/6lowpan/modules.order;   echo net/ieee802154/ieee802154.ko;   echo net/ieee802154/ieee802154_socket.ko; :; } > net/ieee802154/modules.order
