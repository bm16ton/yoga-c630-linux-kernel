cmd_arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.dts.tmp arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb -b 0 -iarch/arm64/boot/dts/marvell/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.d.dtc.tmp arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.dts.tmp ; cat arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.d.pre.tmp arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.d.dtc.tmp > arch/arm64/boot/dts/marvell/.ac5-98dx35xx-rd.dtb.d

source_arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb := arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dts

deps_arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb := \
  arch/arm64/boot/dts/marvell/ac5-98dx35xx.dtsi \
  arch/arm64/boot/dts/marvell/ac5-98dx25xx.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \

arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb: $(deps_arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb)

$(deps_arch/arm64/boot/dts/marvell/ac5-98dx35xx-rd.dtb):
