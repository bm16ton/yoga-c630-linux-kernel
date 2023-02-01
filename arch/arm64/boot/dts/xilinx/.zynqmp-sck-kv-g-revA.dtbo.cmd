cmd_arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo := gcc -E -Wp,-MMD,arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.dts.tmp arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo -b 0 -iarch/arm64/boot/dts/xilinx/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.d.dtc.tmp arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.dts.tmp ; cat arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.d.pre.tmp arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.d.dtc.tmp > arch/arm64/boot/dts/xilinx/.zynqmp-sck-kv-g-revA.dtbo.d

source_arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo := arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dts

deps_arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo := \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/net/ti-dp83867.h \
  scripts/dtc/include-prefixes/dt-bindings/phy/phy.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/pinctrl-zynqmp.h \

arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo: $(deps_arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo)

$(deps_arch/arm64/boot/dts/xilinx/zynqmp-sck-kv-g-revA.dtbo):
