cmd_arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.dts.tmp arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb -b 0 -iarch/arm64/boot/dts/allwinner/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.d.dtc.tmp arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.dts.tmp ; cat arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.d.pre.tmp arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.d.dtc.tmp > arch/arm64/boot/dts/allwinner/.sun50i-a64-pine64-lts.dtb.d

source_arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb := arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dts

deps_arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  arch/arm64/boot/dts/allwinner/sun50i-a64-sopine-baseboard.dts \
  arch/arm64/boot/dts/allwinner/sun50i-a64-sopine.dtsi \
  arch/arm64/boot/dts/allwinner/sun50i-a64.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun50i-a64-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun6i-rtc.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun8i-de2.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/sun8i-r-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun50i-a64-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun8i-de2.h \
  scripts/dtc/include-prefixes/dt-bindings/reset/sun8i-r-ccu.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/arm64/boot/dts/allwinner/sun50i-a64-cpu-opp.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  arch/arm64/boot/dts/allwinner/axp803.dtsi \

arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb: $(deps_arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb)

$(deps_arch/arm64/boot/dts/allwinner/sun50i-a64-pine64-lts.dtb):
