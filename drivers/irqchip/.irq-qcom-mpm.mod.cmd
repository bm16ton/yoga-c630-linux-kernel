cmd_drivers/irqchip/irq-qcom-mpm.mod := printf '%s\n'   irq-qcom-mpm.o | awk '!x[$$0]++ { print("drivers/irqchip/"$$0) }' > drivers/irqchip/irq-qcom-mpm.mod
