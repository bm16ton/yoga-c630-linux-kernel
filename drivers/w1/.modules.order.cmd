cmd_drivers/w1/modules.order := {   cat drivers/w1/masters/modules.order;   cat drivers/w1/slaves/modules.order;   echo drivers/w1/wire.ko; :; } > drivers/w1/modules.order
