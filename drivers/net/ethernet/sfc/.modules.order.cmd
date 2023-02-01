cmd_drivers/net/ethernet/sfc/modules.order := {   echo drivers/net/ethernet/sfc/sfc.ko;   cat drivers/net/ethernet/sfc/falcon/modules.order; :; } > drivers/net/ethernet/sfc/modules.order
