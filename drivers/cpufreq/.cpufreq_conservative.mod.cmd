cmd_drivers/cpufreq/cpufreq_conservative.mod := printf '%s\n'   cpufreq_conservative.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cpufreq_conservative.mod
