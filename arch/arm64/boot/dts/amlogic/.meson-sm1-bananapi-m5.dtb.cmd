cmd_arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.dts.tmp arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb -b 0 -iarch/arm64/boot/dts/amlogic/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.d.dtc.tmp arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.dts.tmp ; cat arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.d.pre.tmp arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.d.dtc.tmp > arch/arm64/boot/dts/amlogic/.meson-sm1-bananapi-m5.dtb.d

source_arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb := arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dts

deps_arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb := \
  arch/arm64/boot/dts/amlogic/meson-sm1.dtsi \
  arch/arm64/boot/dts/amlogic/meson-g12-common.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/phy/phy.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/g12a-clkc.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/g12a-aoclkc.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/amlogic,meson-g12a-reset.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/axg-audio-clkc.h \
  scripts/dtc/include-prefixes/dt-bindings/power/meson-sm1-power.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/amlogic,meson-axg-audio-arb.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/amlogic,meson-g12a-audio-reset.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/meson-g12a-gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/sound/meson-g12a-toacodec.h \
  scripts/dtc/include-prefixes/dt-bindings/sound/meson-g12a-tohdmitx.h \

arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb: $(deps_arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb)

$(deps_arch/arm64/boot/dts/amlogic/meson-sm1-bananapi-m5.dtb):
