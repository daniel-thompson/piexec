// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#include "syscalls.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t sys_c_read()
{
	int c = getchar();
	if (c == EOF)
		exit(0);

	return c;
}

void sys_c_write(uint32_t c)
{
	putchar(c);
}

#define SYS(x) .x = sys_##x
struct syscalls syscall_table = {
	SYS(c_read),
	SYS(c_write),
};
