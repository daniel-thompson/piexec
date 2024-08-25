// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2024 Daniel Thompson

#define _DEFAULT_SOURCE

#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "sys/elf32.h"
#include "syscalls.h"

typedef int (*entrypoint_t)(int argc, char *argv[], struct syscalls *tbl);

struct prog {
	entrypoint_t entrypoint;
};

struct prog load_elf(const char *fname)
{
	size_t sz;

	FILE *f = fopen(fname, "r");

	Elf32_Ehdr ehdr;
	sz = fread(&ehdr, sizeof(Elf32_Ehdr), 1, f);
	assert(sz == 1);
	// TODO: check ident, type and machine
	assert(ehdr.e_type == ET_EXEC);

	(void) fseek(f, ehdr.e_phoff, SEEK_SET);
	Elf32_Phdr phdr[8];
	// p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_flags, p_align
	assert(ehdr.e_phentsize == sizeof(Elf32_Phdr));
	assert(ehdr.e_phnum <= 8);
	sz = fread(&phdr, sizeof(Elf32_Phdr), ehdr.e_phnum, f);
	assert(sz == ehdr.e_phnum);

	char *segment = mmap(NULL, phdr[0].p_memsz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
	assert(segment != MAP_FAILED);
	(void) fseek(f, phdr[0].p_offset, SEEK_SET);
	sz = fread(segment, 1, phdr[0].p_filesz, f);
	assert(sz == phdr[0].p_filesz);
	__builtin___clear_cache(segment, segment+phdr[0].p_filesz);

	struct prog p = {
		.entrypoint = (void *) (segment - phdr[0].p_vaddr + ehdr.e_entry),
	};

	return p;
}

int main(int argc, char *argv[])
{
	struct prog p;

	if (argc <= 1) {
		p = load_elf("tests/hello");
		return p.entrypoint(0, NULL, &syscall_table);
	}

	p = load_elf(argv[1]);
	return p.entrypoint(argc-1, argv+1, &syscall_table);
}
