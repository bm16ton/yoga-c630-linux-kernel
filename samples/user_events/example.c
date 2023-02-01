// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2021, Microsoft Corporation.
 *
 * Authors:
 *   Beau Belgrave <beaub@linux.microsoft.com>
 */

#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
<<<<<<< HEAD
#include <asm/bitsperlong.h>
#include <endian.h>
#include <linux/user_events.h>

#if __BITS_PER_LONG == 64
#define endian_swap(x) htole64(x)
#else
#define endian_swap(x) htole32(x)
#endif

=======
#include <linux/user_events.h>

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
/* Assumes debugfs is mounted */
const char *data_file = "/sys/kernel/debug/tracing/user_events_data";
const char *status_file = "/sys/kernel/debug/tracing/user_events_status";

<<<<<<< HEAD
static int event_status(long **status)
=======
static int event_status(char **status)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	int fd = open(status_file, O_RDONLY);

	*status = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ,
		       MAP_SHARED, fd, 0);

	close(fd);

	if (*status == MAP_FAILED)
		return -1;

	return 0;
}

<<<<<<< HEAD
static int event_reg(int fd, const char *command, long *index, long *mask,
		     int *write)
=======
static int event_reg(int fd, const char *command, int *status, int *write)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
{
	struct user_reg reg = {0};

	reg.size = sizeof(reg);
	reg.name_args = (__u64)command;

	if (ioctl(fd, DIAG_IOCSREG, &reg) == -1)
		return -1;

<<<<<<< HEAD
	*index = reg.status_bit / __BITS_PER_LONG;
	*mask = endian_swap(1L << (reg.status_bit % __BITS_PER_LONG));
=======
	*status = reg.status_index;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	*write = reg.write_index;

	return 0;
}

int main(int argc, char **argv)
{
<<<<<<< HEAD
	int data_fd, write;
	long index, mask;
	long *status_page;
=======
	int data_fd, status, write;
	char *status_page;
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
	struct iovec io[2];
	__u32 count = 0;

	if (event_status(&status_page) == -1)
		return errno;

	data_fd = open(data_file, O_RDWR);

<<<<<<< HEAD
	if (event_reg(data_fd, "test u32 count", &index, &mask, &write) == -1)
=======
	if (event_reg(data_fd, "test u32 count", &status, &write) == -1)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		return errno;

	/* Setup iovec */
	io[0].iov_base = &write;
	io[0].iov_len = sizeof(write);
	io[1].iov_base = &count;
	io[1].iov_len = sizeof(count);

ask:
	printf("Press enter to check status...\n");
	getchar();

	/* Check if anyone is listening */
<<<<<<< HEAD
	if (status_page[index] & mask) {
=======
	if (status_page[status]) {
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		/* Yep, trace out our data */
		writev(data_fd, (const struct iovec *)io, 2);

		/* Increase the count */
		count++;

		printf("Something was attached, wrote data\n");
	}

	goto ask;

	return 0;
}
