// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#include "syscalls.h"

struct syscalls *syscall_table;

int main(int argc, char *argv[]);

int _start(int argc, char *argv[], struct syscalls *tbl)
{
	syscall_table = tbl;
	return main(argc, argv);
}
