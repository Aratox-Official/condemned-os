[BITS 16]
[ORG 0x7C00]

start:
    ; Disable interrupts
    cli
    
    ; Load kernel
    mov ax, 0x1000
    mov es, ax
    mov bx, 0x0000
    mov ah, 0x02
    mov al, 0x10
    mov ch, 0x00
    mov dh, 0x00
    mov dl, 0x80
    int 0x13
    
    ; Switch to protected mode
    mov ax, 0x2401
    int 0x15
    mov ax, 0x3
    int 0x10
    
    ; Jump to kernel
    jmp 0x1000:0x0000

times 510-($-$$) db 0
dw 0xAA55
