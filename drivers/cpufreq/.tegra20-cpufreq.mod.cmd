cmd_drivers/cpufreq/tegra20-cpufreq.mod := printf '%s\n'   tegra20-cpufreq.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/tegra20-cpufreq.mod
