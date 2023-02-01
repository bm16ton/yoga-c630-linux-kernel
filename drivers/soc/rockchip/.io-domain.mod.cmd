cmd_drivers/soc/rockchip/io-domain.mod := printf '%s\n'   io-domain.o | awk '!x[$$0]++ { print("drivers/soc/rockchip/"$$0) }' > drivers/soc/rockchip/io-domain.mod
