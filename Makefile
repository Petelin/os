#!Makefile
# 项目信息

CC = i386-elf-gcc
LD = i386-elf-ld
OBCP = i386-elf-objcopy
ASM = nasm

C_FLAGS = -fno-builtin -Wall -ggdb  -gstabs -fno-stack-protector -nostdinc -Ilibs -Ikernel -g -m32 -c
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs

C_LIB_SOURCES = $(shell find libs -name "*.c")
C_LIB_OBJECTS = $(patsubst libs/%.c, temp/%.o, $(C_LIB_SOURCES))

C_KERNEL_SOURCES = $(shell find kernel -name "*.c")
C_KERNEL_OBJECTS = $(patsubst kernel/%.c, temp/%.o, $(C_KERNEL_SOURCES))

S_KERNEL_SOURCES = $(shell find kernel -name "*.s")
S_KERNEL_OBJECTS = $(patsubst kernel/%.s, temp/%.o, $(S_KERNEL_SOURCES))

all: $(C_LIB_OBJECTS) bin/floppy.img

bin/floppy.img: bin/bootloader bin/kernel
	dd bs=512 count=3000 if=/dev/zero of=bin/floppy.img
	dd bs=512 if=bin/bootloader of=bin/floppy.img conv=notrunc
	dd bs=512 if=bin/kernel of=bin/floppy.img seek=1 conv=notrunc

bin/bootloader: bin/sign boot/bootasm.s boot/bootmain.c
	$(CC) $(C_FLAGS) -Iboot -Os boot/bootasm.S -o temp/bootasm.o
	$(CC) $(C_FLAGS) -I. -Os boot/bootmain.c -o temp/bootmain.o
	$(LD) -m elf_i386 -nostdlib -N -e start -Ttext 0x7C00 temp/bootasm.o temp/bootmain.o -o temp/bootloader.out
	$(OBCP) -S -O binary temp/bootloader.out temp/bootloader
	bin/sign temp/bootloader bin/bootloader

bin/sign: scripts/sign.c
	gcc scripts/sign.c -o bin/sign

bin/kernel: $(S_KERNEL_OBJECTS) $(C_LIB_OBJECTS) $(C_KERNEL_OBJECTS) 
	$(LD) $(LD_FLAGS) $(S_KERNEL_OBJECTS) $(C_LIB_OBJECTS) $(C_KERNEL_OBJECTS)  -o bin/kernel

$(C_LIB_OBJECTS): temp/%.o : libs/%.c
	@echo 编译libs...
	$(CC) $(C_FLAGS) -O3 $< -o $@

$(C_KERNEL_OBJECTS): temp/%.o : kernel/%.c
	@echo 编译kernel...
	$(CC) $(C_FLAGS) $< -o $@ 

$(S_KERNEL_OBJECTS): temp/%.o : kernel/%.s
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) -o $@ $<

.PHONY:qemu
qemu: bin/floppy.img
	qemu-system-i386 -parallel stdio -hda bin/floppy.img -serial null -boot a

.PHONY:debug
debug: bin/floppy.img
	qemu-system-i386 -parallel stdio -hda bin/floppy.img -serial null -S -s &
	i386-elf-gdb -ex 'target remote localhost:1234' \
		-ex 'set architecture i386' \
		-ex 'set disassembly-flavor intel' \
	    -ex 'break *0x100000' \
		-ex 'continue' \
		-ex 'layout asm'\
		-ex 'ni' \
		
		#-ex 'set disassembly-flavor intel' \
#-ex 'break *0x7c00' \

RM := rm -r
.PHONY:clean
clean:
	-$(RM) -f bin/*
	-$(RM) -f $(C_LIB_OBJECTS) $(C_KERNEL_OBJECTS)

