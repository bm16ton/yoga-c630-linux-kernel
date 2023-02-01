cmd_arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.dts.tmp arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb -b 0 -iarch/arm64/boot/dts/amd/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.d.dtc.tmp arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.dts.tmp ; cat arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.d.pre.tmp arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.d.dtc.tmp > arch/arm64/boot/dts/amd/.amd-overdrive-rev-b1.dtb.d

source_arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb := arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dts

deps_arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb := \
  arch/arm64/boot/dts/amd/amd-seattle-soc.dtsi \
  arch/arm64/boot/dts/amd/amd-seattle-clks.dtsi \
  arch/arm64/boot/dts/amd/amd-seattle-cpus.dtsi \
  arch/arm64/boot/dts/amd/amd-seattle-xgbe-b.dtsi \

arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb: $(deps_arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb)

$(deps_arch/arm64/boot/dts/amd/amd-overdrive-rev-b1.dtb):
