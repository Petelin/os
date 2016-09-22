section .text:
    global start  
start:
org 07c00h          ; 在计算标号地址的时候从07c00H 开始算 
    mov ax, 0
    mov ds, ax
    mov es, ax
    call clear
    call DispStr         ; 调用显示字符串例程
    jmp $          ; 无限循环
DispStr:
    mov ax, BootMessage
    mov bp, ax          ; ES:BP = 串地址
    mov cx, 16          ; CX = 串长度
    mov ax, 01301h      ; AH = 13, AL = 01h
    mov bx, 000ch       ; 页号为0(BH = 0) 黑底红字(BL = 0Ch,高亮)
    mov dl, 0
    int 10h         ; 10h 号中断
    ret
clear:
    push ds
    push dx
    mov ax,0b800H
    mov ds,ax
    mov si, 0
    mov dx, 0
    mov cx, 25
    s2: 
        mov ax, 160
        push dx
        mul dx
        pop dx
        mov si, ax
        mov bx, 0
        push cx
        mov cx, 80
        s1: mov byte [si+bx], ' '
            mov byte [si+bx + 1], 1cH
            add bx, 2
            loop s1
        add dx, 1
        pop cx
        loop s2
    pop dx
    pop ds
    ret

BootMessage:        db  "Hello, OS world!"
times   510-($-$$)   db  0   ; 填充剩下的空间，使生成的二进制代码恰好为512字节
dw  0xaa55              ; 结束标志
