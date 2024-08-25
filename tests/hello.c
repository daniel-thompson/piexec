// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#if 0
#include "syscalls.h"

struct syscalls *syscall_table;

int putchar(int c) {
	syscall_table->c_write(c);
	return 0;
}

int main(int argc, char *argv[])
{
	const char s[] = "Hello world\n";
	const char *p = s;

	while (*p)
		putchar(*p++);

	return 0;
}

int _start(int argc, char *argv[], struct syscalls *tbl)
{
	syscall_table = tbl;
	return main(argc, argv);
}
#else
#include <stdio.h>
int main(int argc, char *argv[])
{
	const char s[] = "Hello world\n";
	const char *p = s;

	while (*p)
		putchar(*p++);

	return 0;
}
#endif
