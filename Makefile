#!Makefile
# 项目信息

CC = i386-elf-gcc
LD = i386-elf-ld
OBCP = i386-elf-objcopy

C_FLAGS = -fno-builtin -Wall -ggdb -m32 -gstabs  -nostdinc  -fno-stack-protector  -Os -nostdinc -c
BOOT_LD_FLAGS = -nostdlib -N -e start -Ttext 0x7C00
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib

all: bin/floppy.img

bin/floppy.img: bin/bootloader
	dd bs=512 count=1000 if=bin/bootloader of=bin/floppy.img conv=notrunc

bin/bootloader: temp/boot temp/bootasm bin/sign
	$(LD) $(BOOT_LD_FLAGS) temp/bootasm temp/boot -o temp/bootloader.out
	$(OBCP) -S -O binary temp/bootloader.out temp/bootloader
	bin/sign temp/bootloader bin/bootloader

bin/sign:
	gcc scripts/sign.c -o bin/sign

temp/bootasm: boot/bootasm.s
	$(CC) $(C_FLAGS) boot/bootasm.s -o temp/bootasm

temp/boot: boot/boot.c
	$(CC) $(C_FLAGS) boot/boot.c -o temp/boot



.PHONY:qemu
qemu:
	qemu -fda bin/floppy.img -boot a

.PHONY:debug
debug:
	qemu -S -s -fda floppy.img -boot a &
	sleep 1
	cgdb -x scripts/gdbinit

