cmd_drivers/cpufreq/cpufreq_userspace.mod := printf '%s\n'   cpufreq_userspace.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cpufreq_userspace.mod
