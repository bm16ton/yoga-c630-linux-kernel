cmd_drivers/net/ethernet/amd/modules.order := {   echo drivers/net/ethernet/amd/pcnet32.ko;   cat drivers/net/ethernet/amd/xgbe/modules.order; :; } > drivers/net/ethernet/amd/modules.order
