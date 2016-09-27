#!Makefile
# 项目信息

CC = i386-elf-gcc
LD = i386-elf-ld
OBCP = i386-elf-objcopy

C_FLAGS = -fno-builtin -Wall -ggdb -m32 -gstabs -fno-stack-protector  -Os -nostdinc -Iboot -Ilibs -c  -gstabs+
BOOT_LD_FLAGS = -m elf_i386 -nostdlib -N -e start -Ttext 0x7C00
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib

OBJECTS = io.o

all: $(OBJECTS) bin/floppy.img

bin/floppy.img: bin/bootloader
	dd bs=512 count=1000 if=/dev/zero of=bin/floppy.img
	dd bs=512 if=bin/bootloader of=bin/floppy.img conv=notrunc

bin/bootloader: bin/sign
	$(LD) $(BOOT_LD_FLAGS) ./temp/bootasm $(shell find . -name "*.o") -o ./temp/bootloader.out
	$(OBCP) -S -O binary temp/bootloader.out temp/bootloader
	bin/sign temp/bootloader bin/bootloader

bin/sign: scripts/sign.c
	gcc scripts/sign.c -o bin/sign

$(OBJECTS): %.o : libs/%.c
	@echo 编译libs c...
	$(CC) $(C_FLAGS) $< -o temp/$(OBJECTS)
	$(CC) $(C_FLAGS) boot/bootasm.S -o temp/bootasm
	$(CC) $(C_FLAGS) boot/boot.c -o temp/boot.o

.PHONY:qemu
qemu:
	qemu-system-i386 -fda bin/floppy.img -boot a

.PHONY:debug
debug:
	qemu -hda bin/floppy.img -S -s &
	gdb -ex 'target remote localhost:1234' \
	    -ex 'set disassembly-flavor intel' \
		-ex 'set architecture i386' \
	    -ex 'break *0x7c00' \
		-ex 'continue'


.PHONY:clean
clean:
	$(shell rm -rf bin/*)
	$(shell rm -rf temp/*)
