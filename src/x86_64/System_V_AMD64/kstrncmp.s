; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kstrncmp

; rax = (return)    bool
; rdi = (1st)       const char*     src
; rsi = (2nd)       const char*     dst
; rdx  = (3rd)       size_t          count
asm_kstrncmp:
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080

    test    rdx, rdx
    jz      .equal

    cmp     rdx, 8
    jb      .unaligned_compare

    mov     r10, [rdi]
    mov     r11, [rsi]
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_compare:
    mov     r10b, [rdi]
    mov     r11b, [rsi]
    cmp     r10b, r11b
    jne     .nequal

    test    r10b, r10b
    jz      .equal

    dec     rdx
    jz      .equal

    inc     rdi
    inc     rsi
    jmp     .unaligned_compare

.align:
    test    rdi, 7
    jz      .aligned_compare

    mov     r10b, [rdi]
    mov     r11b, [rsi]
    cmp     r10b, r11b
    jne     .nequal

    test    r10b, r10b
    jz      .equal

    dec     rdx
    jz      .equal

    inc     rdi
    inc     rsi
    jmp     .align

.aligned_compare:
    mov     r10, [rdi]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rsi]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_compare

    mov     r10, [rdi]
    mov     r11, [rsi]
    cmp     r10, r11
    jne     .nequal

    add     rdi, 8
    add     rsi, 8
    sub     rdx, 8
    jz      .equal

    cmp     rdx, 8
    jb      .unaligned_compare
    jmp     .aligned_compare

.equal:
    mov     rax, 1
    jmp     .done

.nequal:
    mov     rax, 0

.done:
    pop r13
    pop r12
    ret