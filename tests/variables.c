// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#include "syscalls.h"

int a = 'a';
int b;

int _start(int argc, char *argv[], struct syscalls *tbl)
{
	tbl->c_write(a + b);
	tbl->c_write('\n');

	return 0;
}
