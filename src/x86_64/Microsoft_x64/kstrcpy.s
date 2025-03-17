; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kstrcpy

; rax = (return) void
; rcx =    (1st) const char*    dst
; rdx =    (2nd) const char*    src
kstrcpy:
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080

    mov     r10, rcx
    mov     r11, rdx
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_copy:
    mov     r10b, [rcx]
    test    r10b, r10b
    jz      .done

    mov     r10b, [rdx]
    test    r10b, r10b
    jz      .done

    mov     [rcx], r10b

    inc     rcx
    inc     rdx
    jmp     .unaligned_copy

.align:
    test    rcx, 7
    jz      .aligned_copy

    mov     r10b, [rcx]
    test    r10b, r10b
    jz      .done

    mov     r10b, [rdx]
    test    r10b, r10b
    jz      .done
    
    mov     [rcx], r10b

    inc     rcx
    inc     rdx
    jmp     .align

.aligned_copy:
    mov     r10, [rdx]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_copy

    mov     r10, [rdx]
    mov     [rcx], r10

    add     rcx, 8
    add     rdx, 8
    jb      .unaligned_copy

.done:
    pop r13
    pop r12
    ret