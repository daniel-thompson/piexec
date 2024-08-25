#ifndef PIEXEC_SYSCALLS_H_
#define PIEXEC_SYSCALLS_H_

#include <stdint.h>

struct syscalls {
	uint32_t (*c_read)();
	void (*c_write)(uint32_t c);
};

#ifdef _PIEXEC_HOST
extern struct syscalls syscall_table;
#else
extern struct syscalls *syscall_table;
#endif

#endif // PIEXEC_SYSCALLS_H_
