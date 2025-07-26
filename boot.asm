ORG 0
[BITS 16]

_start:
    jmp short start
    nop
    times 33 db 0



start:
    jmp 0x7C0:prog

prog:
    cli
    mov ax, 0x7C0
    mov ds, ax
    mov es, ax
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7C00
    call hello
    sti
    jmp$

hello:
    mov si, msg
    call print
    jmp $

print:
    mov bx,0
    .loop:
        lodsb
        cmp al,0
        je .done
        call .print_char
        jmp .loop

    .print_char:
        mov ah,0eh
        int 0x10
        ret

    .done:
        ret

msg : db 'Hello from ring-0', 0


times 510 - ($-$$) db 0
dw 0xAA55

buffer: