cmd_drivers/target/iscsi/modules.order := {   echo drivers/target/iscsi/iscsi_target_mod.ko;   cat drivers/target/iscsi/cxgbit/modules.order; :; } > drivers/target/iscsi/modules.order
