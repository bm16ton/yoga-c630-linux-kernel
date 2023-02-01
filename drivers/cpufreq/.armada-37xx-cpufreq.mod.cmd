cmd_drivers/cpufreq/armada-37xx-cpufreq.mod := printf '%s\n'   armada-37xx-cpufreq.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/armada-37xx-cpufreq.mod
