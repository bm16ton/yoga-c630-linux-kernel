cmd_arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.dts.tmp arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb -b 0 -iarch/arm64/boot/dts/qcom/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.d.dtc.tmp arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.dts.tmp ; cat arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.d.pre.tmp arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.d.dtc.tmp > arch/arm64/boot/dts/qcom/.msm8996-sony-xperia-tone-kagura.dtb.d

source_arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb := arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dts

deps_arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb := \
  arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone.dtsi \
  arch/arm64/boot/dts/qcom/msm8996.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,gcc-msm8996.h \
    $(wildcard include/config/NOC_CLK_SRC) \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,mmcc-msm8996.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,rpmcc.h \
  scripts/dtc/include-prefixes/dt-bindings/interconnect/qcom,msm8996.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/power/qcom-rpmpd.h \
  scripts/dtc/include-prefixes/dt-bindings/soc/qcom,apr.h \
  scripts/dtc/include-prefixes/dt-bindings/thermal/thermal.h \
  arch/arm64/boot/dts/qcom/pm8994.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/iio/qcom,spmi-vadc.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/spmi/spmi.h \
  arch/arm64/boot/dts/qcom/pmi8994.dtsi \
  arch/arm64/boot/dts/qcom/pmi8996.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/qcom,pmic-gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/qcom,pmic-mpp.h \

arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb: $(deps_arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb)

$(deps_arch/arm64/boot/dts/qcom/msm8996-sony-xperia-tone-kagura.dtb):
