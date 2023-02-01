cmd_arch/arm64/boot/dts/cavium/thunder-88xx.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.dts.tmp arch/arm64/boot/dts/cavium/thunder-88xx.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/cavium/thunder-88xx.dtb -b 0 -iarch/arm64/boot/dts/cavium/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.d.dtc.tmp arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.dts.tmp ; cat arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.d.pre.tmp arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.d.dtc.tmp > arch/arm64/boot/dts/cavium/.thunder-88xx.dtb.d

source_arch/arm64/boot/dts/cavium/thunder-88xx.dtb := arch/arm64/boot/dts/cavium/thunder-88xx.dts

deps_arch/arm64/boot/dts/cavium/thunder-88xx.dtb := \
  arch/arm64/boot/dts/cavium/thunder-88xx.dtsi \

arch/arm64/boot/dts/cavium/thunder-88xx.dtb: $(deps_arch/arm64/boot/dts/cavium/thunder-88xx.dtb)

$(deps_arch/arm64/boot/dts/cavium/thunder-88xx.dtb):
