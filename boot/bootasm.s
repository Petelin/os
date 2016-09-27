.data
    message : .string "hello, world!" 

.code16
.text
    .global start

    start:
        mov %cs, %ax
        mov %ax, %ds
        mov %ax, %es
        call p
        call kern_enter
        jmp .
    p:
        movw $message, %ax
        movw %ax, %bp
        movw $0x16, %cx
        movw $0x1301, %ax
        movw $0x0002, %bx
        movb $0x00, %dl
        int $0x10
        ret

