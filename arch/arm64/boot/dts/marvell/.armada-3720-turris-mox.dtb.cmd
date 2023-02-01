cmd_arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.dts.tmp arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb -b 0 -iarch/arm64/boot/dts/marvell/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.d.dtc.tmp arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.dts.tmp ; cat arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.d.pre.tmp arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.d.dtc.tmp > arch/arm64/boot/dts/marvell/.armada-3720-turris-mox.dtb.d

source_arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb := arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dts

deps_arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/bus/moxtet.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  arch/arm64/boot/dts/marvell/armada-372x.dtsi \
  arch/arm64/boot/dts/marvell/armada-37xx.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \

arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb: $(deps_arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb)

$(deps_arch/arm64/boot/dts/marvell/armada-3720-turris-mox.dtb):
