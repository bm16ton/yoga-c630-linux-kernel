cmd_drivers/cpufreq/cppc_cpufreq.mod := printf '%s\n'   cppc_cpufreq.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cppc_cpufreq.mod
