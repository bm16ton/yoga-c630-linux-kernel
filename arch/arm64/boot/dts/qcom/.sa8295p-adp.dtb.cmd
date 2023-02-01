cmd_arch/arm64/boot/dts/qcom/sa8295p-adp.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.dts.tmp arch/arm64/boot/dts/qcom/sa8295p-adp.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/qcom/sa8295p-adp.dtb -b 0 -iarch/arm64/boot/dts/qcom/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.d.dtc.tmp arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.dts.tmp ; cat arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.d.pre.tmp arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.d.dtc.tmp > arch/arm64/boot/dts/qcom/.sa8295p-adp.dtb.d

source_arch/arm64/boot/dts/qcom/sa8295p-adp.dtb := arch/arm64/boot/dts/qcom/sa8295p-adp.dts

deps_arch/arm64/boot/dts/qcom/sa8295p-adp.dtb := \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/regulator/qcom,rpmh-regulator.h \
  scripts/dtc/include-prefixes/dt-bindings/spmi/spmi.h \
  arch/arm64/boot/dts/qcom/sa8540p.dtsi \
  arch/arm64/boot/dts/qcom/sc8280xp.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,gcc-sc8280xp.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,rpmh.h \
  scripts/dtc/include-prefixes/dt-bindings/interconnect/qcom,sc8280xp.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/mailbox/qcom-ipcc.h \
  scripts/dtc/include-prefixes/dt-bindings/power/qcom-rpmpd.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/qcom,rpmh-rsc.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \

arch/arm64/boot/dts/qcom/sa8295p-adp.dtb: $(deps_arch/arm64/boot/dts/qcom/sa8295p-adp.dtb)

$(deps_arch/arm64/boot/dts/qcom/sa8295p-adp.dtb):
