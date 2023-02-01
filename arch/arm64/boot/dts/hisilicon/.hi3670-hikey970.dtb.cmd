cmd_arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.dts.tmp arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb -b 0 -iarch/arm64/boot/dts/hisilicon/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.d.dtc.tmp arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.dts.tmp ; cat arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.d.pre.tmp arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.d.dtc.tmp > arch/arm64/boot/dts/hisilicon/.hi3670-hikey970.dtb.d

source_arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb := arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dts

deps_arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  arch/arm64/boot/dts/hisilicon/hi3670.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/hi3670-clock.h \
  arch/arm64/boot/dts/hisilicon/hikey970-pinctrl.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/hisi.h \
  arch/arm64/boot/dts/hisilicon/hikey970-pmic.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/spmi/spmi.h \

arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb: $(deps_arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb)

$(deps_arch/arm64/boot/dts/hisilicon/hi3670-hikey970.dtb):
