cmd_arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.dts.tmp arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb -b 0 -iarch/arm64/boot/dts/amlogic/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.d.dtc.tmp arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.dts.tmp ; cat arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.d.pre.tmp arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.d.dtc.tmp > arch/arm64/boot/dts/amlogic/.meson-gxl-s905w-tx3-mini.dtb.d

source_arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb := arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dts

deps_arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb := \
  arch/arm64/boot/dts/amlogic/meson-gxl-s905x.dtsi \
  arch/arm64/boot/dts/amlogic/meson-gxl.dtsi \
  arch/arm64/boot/dts/amlogic/meson-gx.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/power/meson-gxbb-power.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/gxbb-clkc.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/gxbb-aoclkc.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/meson-gxl-gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/amlogic,meson-gxbb-reset.h \
  arch/arm64/boot/dts/amlogic/meson-gxl-mali.dtsi \
  arch/arm64/boot/dts/amlogic/meson-gx-mali450.dtsi \
  arch/arm64/boot/dts/amlogic/meson-gx-p23x-q20x.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/sound/meson-aiu.h \

arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb: $(deps_arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb)

$(deps_arch/arm64/boot/dts/amlogic/meson-gxl-s905w-tx3-mini.dtb):
