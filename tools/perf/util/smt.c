// SPDX-License-Identifier: GPL-2.0-only
#include <string.h>
#include "api/fs/fs.h"
#include "cputopo.h"
#include "smt.h"

<<<<<<< HEAD
bool smt_on(const struct cpu_topology *topology)
=======
/**
 * hweight_str - Returns the number of bits set in str. Stops at first non-hex
 *	       or ',' character.
 */
static int hweight_str(char *str)
{
	int result = 0;

	while (*str) {
		switch (*str++) {
		case '0':
		case ',':
			break;
		case '1':
		case '2':
		case '4':
		case '8':
			result++;
			break;
		case '3':
		case '5':
		case '6':
		case '9':
		case 'a':
		case 'A':
		case 'c':
		case 'C':
			result += 2;
			break;
		case '7':
		case 'b':
		case 'B':
		case 'd':
		case 'D':
		case 'e':
		case 'E':
			result += 3;
			break;
		case 'f':
		case 'F':
			result += 4;
			break;
		default:
			goto done;
		}
	}
done:
	return result;
}

int smt_on(void)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	static bool cached;
	static bool cached_result;
	int fs_value;

	if (cached)
		return cached_result;

<<<<<<< HEAD
	if (sysfs__read_int("devices/system/cpu/smt/active", &fs_value) >= 0)
		cached_result = (fs_value == 1);
	else
		cached_result = cpu_topology__smt_on(topology);

=======
	if (sysfs__read_int("devices/system/cpu/smt/active", &cached_result) >= 0) {
		cached = true;
		return cached_result;
	}

	cached_result = 0;
	ncpu = sysconf(_SC_NPROCESSORS_CONF);
	for (cpu = 0; cpu < ncpu; cpu++) {
		unsigned long long siblings;
		char *str;
		size_t strlen;
		char fn[256];

		snprintf(fn, sizeof fn,
			"devices/system/cpu/cpu%d/topology/thread_siblings", cpu);
		if (sysfs__read_str(fn, &str, &strlen) < 0) {
			snprintf(fn, sizeof fn,
				"devices/system/cpu/cpu%d/topology/core_cpus", cpu);
			if (sysfs__read_str(fn, &str, &strlen) < 0)
				continue;
		}
		/* Entry is hex, but does not have 0x, so need custom parser */
		siblings = hweight_str(str);
		free(str);
		if (siblings > 1) {
			cached_result = 1;
			break;
		}
	}
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	cached = true;
	return cached_result;
}

bool core_wide(bool system_wide, const char *user_requested_cpu_list,
	       const struct cpu_topology *topology)
{
	/* If not everything running on a core is being recorded then we can't use core_wide. */
	if (!system_wide)
		return false;

	/* Cheap case that SMT is disabled and therefore we're inherently core_wide. */
	if (!smt_on(topology))
		return true;

	return cpu_topology__core_wide(topology, user_requested_cpu_list);
}
