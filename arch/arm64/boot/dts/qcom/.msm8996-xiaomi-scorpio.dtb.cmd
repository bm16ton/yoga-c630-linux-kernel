cmd_arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.dts.tmp arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb -b 0 -iarch/arm64/boot/dts/qcom/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.d.dtc.tmp arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.dts.tmp ; cat arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.d.pre.tmp arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.d.dtc.tmp > arch/arm64/boot/dts/qcom/.msm8996-xiaomi-scorpio.dtb.d

source_arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb := arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dts

deps_arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb := \
  arch/arm64/boot/dts/qcom/msm8996-xiaomi-common.dtsi \
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
  scripts/dtc/include-prefixes/dt-bindings/input/input.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/leds/common.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/qcom,pmic-gpio.h \
  arch/arm64/boot/dts/qcom/pmi8996.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/sound/qcom,q6afe.h \
  scripts/dtc/include-prefixes/dt-bindings/sound/qcom,q6dsp-lpass-ports.h \
  scripts/dtc/include-prefixes/dt-bindings/sound/qcom,q6asm.h \
  scripts/dtc/include-prefixes/dt-bindings/sound/qcom,wcd9335.h \

arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb: $(deps_arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb)

$(deps_arch/arm64/boot/dts/qcom/msm8996-xiaomi-scorpio.dtb):
