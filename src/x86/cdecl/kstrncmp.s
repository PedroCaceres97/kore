; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kstrncmp

; rax = bool
; rcx = const char* src
; rdx = const char* dst
; r8  = size_t count
kstrncmp:
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080

    test    r8, r8
    jz      .equal

    cmp     r8, 8
    jb      .unaligned_compare

    mov     r10, [rcx]
    mov     r11, [rdx]
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_compare:
    mov     r10b, [rcx]
    mov     r11b, [rdx]
    cmp     r10b, r11b
    jne     .nequal

    test    r10b, r10b
    jz      .equal

    dec     r8
    jz      .equal

    inc     rcx
    inc     rdx
    jmp     .unaligned_compare

.align:
    test    rcx, 7
    jz      .aligned_compare

    mov     r10b, [rcx]
    mov     r11b, [rdx]
    cmp     r10b, r11b
    jne     .nequal

    test    r10b, r10b
    jz      .equal

    dec     r8
    jz      .equal

    inc     rcx
    inc     rdx
    jmp     .align

.aligned_compare:
    mov     r10, [rcx]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rdx]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rcx]
    mov     r11, [rdx]
    cmp     r10, r11
    jne     .nequal

    add     rcx, 8
    add     rdx, 8
    sub     r8, 8
    jz      .equal

    cmp     r8, 8
    jb      .unaligned_compare
    jmp     .aligned_compare

.equal:
    mov     eax, 1
    jmp     .done

.nequal:
    mov     eax, 0

.done:
    pop r13
    pop r12
    ret