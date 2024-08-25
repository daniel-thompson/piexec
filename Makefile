CC = $(CROSS_COMPILE)gcc
CFLAGS = -g -Os -mthumb -march=armv7-a
LD = $(CROSS_COMPILE)ld
AR = gcc-ar

APPS = coreutils/echo tests/hello #tests/variables
OBJS = csim/csim.o csim/syscalls.o
LIBC_OBJS = libc/stdio.o libc/crt0.o

all : csim/csim $(APPS)

run : all
	csim/csim

clean :
	$(RM) csim/csim $(APPS) libc.a */*.o

csim/csim : CFLAGS := $(CFLAGS) -D_PIEXEC_HOST -Iinclude/
csim/csim : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

libc.a : $(LIBC_OBJS)
	$(AR) rcs $@ $(LIBC_OBJS)
	gcc-ranlib $@

$(APPS) libc.a : CFLAGS := $(CFLAGS) -fpie -flto -nostdinc -Ilibc/include/ -Iinclude/

coreutils/% : coreutils/%.o libc.a
	$(CC) $(CFLAGS) -static-pie -nostdlib -nostartfiles -T libc/app.ld -o $@ $(@:%=%.o) $(LIBC_OBJS)

tests/% : tests/%.o libc.a
	$(CC) $(CFLAGS) -static-pie -nostdlib -nostartfiles -T libc/app.ld -o $@ $(@:%=%.o) libc.a
