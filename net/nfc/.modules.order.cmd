cmd_net/nfc/modules.order := {   echo net/nfc/nfc.ko;   cat net/nfc/nci/modules.order;   cat net/nfc/hci/modules.order;   echo net/nfc/nfc_digital.ko; :; } > net/nfc/modules.order
