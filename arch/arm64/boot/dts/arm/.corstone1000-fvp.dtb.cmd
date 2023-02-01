cmd_arch/arm64/boot/dts/arm/corstone1000-fvp.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.dts.tmp arch/arm64/boot/dts/arm/corstone1000-fvp.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/arm/corstone1000-fvp.dtb -b 0 -iarch/arm64/boot/dts/arm/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.d.dtc.tmp arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.dts.tmp ; cat arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.d.pre.tmp arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.d.dtc.tmp > arch/arm64/boot/dts/arm/.corstone1000-fvp.dtb.d

source_arch/arm64/boot/dts/arm/corstone1000-fvp.dtb := arch/arm64/boot/dts/arm/corstone1000-fvp.dts

deps_arch/arm64/boot/dts/arm/corstone1000-fvp.dtb := \
  arch/arm64/boot/dts/arm/corstone1000.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \

arch/arm64/boot/dts/arm/corstone1000-fvp.dtb: $(deps_arch/arm64/boot/dts/arm/corstone1000-fvp.dtb)

$(deps_arch/arm64/boot/dts/arm/corstone1000-fvp.dtb):
