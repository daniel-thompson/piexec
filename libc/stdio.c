// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#include <stdio.h>

#include "syscalls.h"

int getchar() {
	return syscall_table->c_read();
}

int putchar(int c) {
	syscall_table->c_write(c);
	return 0;
}
