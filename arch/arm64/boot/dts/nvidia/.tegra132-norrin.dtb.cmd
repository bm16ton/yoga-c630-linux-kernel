cmd_arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.dts.tmp arch/arm64/boot/dts/nvidia/tegra132-norrin.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb -b 0 -iarch/arm64/boot/dts/nvidia/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.d.dtc.tmp arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.dts.tmp ; cat arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.d.pre.tmp arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.d.dtc.tmp > arch/arm64/boot/dts/nvidia/.tegra132-norrin.dtb.d

source_arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb := arch/arm64/boot/dts/nvidia/tegra132-norrin.dts

deps_arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  arch/arm64/boot/dts/nvidia/tegra132.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/tegra124-car.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/tegra124-car-common.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/tegra-gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/memory/tegra124-mc.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/pinctrl-tegra.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/pinctrl-tegra-xusb.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/tegra124-soctherm.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/tegra-pmc.h \
  arch/arm64/boot/dts/nvidia/tegra132-peripherals-opp.dtsi \

arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb: $(deps_arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb)

$(deps_arch/arm64/boot/dts/nvidia/tegra132-norrin.dtb):
