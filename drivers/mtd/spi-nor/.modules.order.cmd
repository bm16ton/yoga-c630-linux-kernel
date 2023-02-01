cmd_drivers/mtd/spi-nor/modules.order := {   echo drivers/mtd/spi-nor/spi-nor.ko;   cat drivers/mtd/spi-nor/controllers/modules.order; :; } > drivers/mtd/spi-nor/modules.order
