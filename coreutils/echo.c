// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#include <stdio.h>

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		for (const char *p = argv[i]; *p; p++) {
			putchar(*p);
		}
	}
	putchar('\n');

	return 0;
}
