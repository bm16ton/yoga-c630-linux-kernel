// SPDX-License-Identifier: GPL-2.0
#include <test_progs.h>

void test_tcp_estats(void)
{
	const char *file = "./test_tcp_estats.bpf.o";
	int err, prog_fd;
	struct bpf_object *obj;

	err = bpf_prog_test_load(file, BPF_PROG_TYPE_TRACEPOINT, &obj, &prog_fd);
<<<<<<< HEAD
	if (!ASSERT_OK(err, ""))
=======
	CHECK(err, "", "err %d errno %d\n", err, errno);
	if (err)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
		return;

	bpf_object__close(obj);
}
