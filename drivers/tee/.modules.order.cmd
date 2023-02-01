cmd_drivers/tee/modules.order := {   echo drivers/tee/tee.ko;   cat drivers/tee/optee/modules.order; :; } > drivers/tee/modules.order
