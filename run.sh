#!/bin/bash

debug-qemu(){

qemu-system-i386 -hda os.img -S -s &
gdb -ex 'target remote localhost:1234' \
    -ex 'set disassembly-flavor intel' \
    -ex 'set architecture i8086' \
    -ex 'set disassemble-next-line off' \
    -ex 'break *0x7c00' \
    -ex 'continue'
    -ex 'display /10000i $pc'
}
makeimg(){
    nasm bootloader.asm && dd bs=512 count=1 if=bootloader of=os.img conv=notrunc  
}
runimg(){
    qemu-system-i386 -hda os.img
}



