cmd_arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb := gcc -E -Wp,-MMD,arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.dts.tmp arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dts ; ./scripts/dtc/dtc -o arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb -b 0 -iarch/arm64/boot/dts/qcom/ -i./scripts/dtc/include-prefixes -Wno-interrupt_provider -Wno-unit_address_vs_reg -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address   -d arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.d.dtc.tmp arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.dts.tmp ; cat arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.d.pre.tmp arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.d.dtc.tmp > arch/arm64/boot/dts/qcom/.msm8992-msft-lumia-octagon-talkman.dtb.d

source_arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb := arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dts

deps_arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb := \
  arch/arm64/boot/dts/qcom/msm8992.dtsi \
  arch/arm64/boot/dts/qcom/msm8994.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/arm-gic.h \
  scripts/dtc/include-prefixes/dt-bindings/interrupt-controller/irq.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,gcc-msm8994.h \
    $(wildcard include/config/NOC_CLK_SRC) \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,mmcc-msm8994.h \
  scripts/dtc/include-prefixes/dt-bindings/clock/qcom,rpmcc.h \
  scripts/dtc/include-prefixes/dt-bindings/gpio/gpio.h \
  scripts/dtc/include-prefixes/dt-bindings/power/qcom-rpmpd.h \
  arch/arm64/boot/dts/qcom/msm8994-msft-lumia-octagon.dtsi \
  arch/arm64/boot/dts/qcom/pm8994.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/iio/qcom,spmi-vadc.h \
  scripts/dtc/include-prefixes/dt-bindings/input/linux-event-codes.h \
  scripts/dtc/include-prefixes/dt-bindings/spmi/spmi.h \
  arch/arm64/boot/dts/qcom/pmi8994.dtsi \
  scripts/dtc/include-prefixes/dt-bindings/input/gpio-keys.h \
  scripts/dtc/include-prefixes/dt-bindings/pinctrl/qcom,pmic-gpio.h \

arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb: $(deps_arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb)

$(deps_arch/arm64/boot/dts/qcom/msm8992-msft-lumia-octagon-talkman.dtb):
