cmd_arch/arm64/boot/dts/apm/apm-mustang.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/apm/.apm-mustang.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/apm/.apm-mustang.dtb.dts.tmp arch/arm64/boot/dts/apm/apm-mustang.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/apm/apm-mustang.dtb -b 0 -iarch/arm64/boot/dts/apm/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/apm/.apm-mustang.dtb.d.dtc.tmp arch/arm64/boot/dts/apm/.apm-mustang.dtb.dts.tmp ; cat arch/arm64/boot/dts/apm/.apm-mustang.dtb.d.pre.tmp arch/arm64/boot/dts/apm/.apm-mustang.dtb.d.dtc.tmp > arch/arm64/boot/dts/apm/.apm-mustang.dtb.d

source_arch/arm64/boot/dts/apm/apm-mustang.dtb := arch/arm64/boot/dts/apm/apm-mustang.dts

deps_arch/arm64/boot/dts/apm/apm-mustang.dtb := \
  arch/arm64/boot/dts/apm/apm-storm.dtsi \

arch/arm64/boot/dts/apm/apm-mustang.dtb: $(deps_arch/arm64/boot/dts/apm/apm-mustang.dtb)

$(deps_arch/arm64/boot/dts/apm/apm-mustang.dtb):
