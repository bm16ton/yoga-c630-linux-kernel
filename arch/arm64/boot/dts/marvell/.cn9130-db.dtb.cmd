cmd_arch/arm64/boot/dts/marvell/cn9130-db.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/marvell/.cn9130-db.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/marvell/.cn9130-db.dtb.dts.tmp arch/arm64/boot/dts/marvell/cn9130-db.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/marvell/cn9130-db.dtb -b 0 -iarch/arm64/boot/dts/marvell/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/marvell/.cn9130-db.dtb.d.dtc.tmp arch/arm64/boot/dts/marvell/.cn9130-db.dtb.dts.tmp ; cat arch/arm64/boot/dts/marvell/.cn9130-db.dtb.d.pre.tmp arch/arm64/boot/dts/marvell/.cn9130-db.dtb.d.dtc.tmp > arch/arm64/boot/dts/marvell/.cn9130-db.dtb.d

source_arch/arm64/boot/dts/marvell/cn9130-db.dtb := arch/arm64/boot/dts/marvell/cn9130-db.dts

deps_arch/arm64/boot/dts/marvell/cn9130-db.dtb := \
  arch/arm64/boot/dts/marvell/cn9130-db.dtsi \
  arch/arm64/boot/dts/marvell/cn9130.dtsi \
  arch/arm64/boot/dts/marvell/armada-ap807-quad.dtsi \
  arch/arm64/boot/dts/marvell/armada-ap807.dtsi \
  arch/arm64/boot/dts/marvell/armada-ap80x.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/arm64/boot/dts/marvell/armada-cp115.dtsi \
  arch/arm64/boot/dts/marvell/armada-cp11x.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/mvebu-icu.h \
  arch/arm64/boot/dts/marvell/armada-common.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \

arch/arm64/boot/dts/marvell/cn9130-db.dtb: $(deps_arch/arm64/boot/dts/marvell/cn9130-db.dtb)

$(deps_arch/arm64/boot/dts/marvell/cn9130-db.dtb):
