cmd_block/modules.order := {   cat block/partitions/modules.order;   echo block/kyber-iosched.ko;   echo block/bfq.ko; :; } > block/modules.order
