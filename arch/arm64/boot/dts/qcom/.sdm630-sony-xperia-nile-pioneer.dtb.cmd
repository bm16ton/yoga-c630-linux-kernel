cmd_arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.dts.tmp arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb -b 0 -iarch/arm64/boot/dts/qcom/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.d.dtc.tmp arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.dts.tmp ; cat arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.d.pre.tmp arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.d.dtc.tmp > arch/arm64/boot/dts/qcom/.sdm630-sony-xperia-nile-pioneer.dtb.d

source_arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb := arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dts

deps_arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb := \
  arch/arm64/boot/dts/qcom/sdm630.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,gcc-sdm660.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,gpucc-sdm660.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,mmcc-sdm660.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,rpmcc.h \
  scripts/dtc/include-prefixes/dt-bindings/interconnect/qcom,sdm660.h \
  scripts/dtc/include-prefixes/dt-bindings/power/qcom-rpmpd.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/qcom,apr.h \
  arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile.dtsi \
  arch/arm64/boot/dts/qcom/pm660.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/iio/qcom,spmi-vadc.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/spmi/spmi.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/arm64/boot/dts/qcom/pm660l.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/input/gpio-keys.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \

arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb: $(deps_arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb)

$(deps_arch/arm64/boot/dts/qcom/sdm630-sony-xperia-nile-pioneer.dtb):
