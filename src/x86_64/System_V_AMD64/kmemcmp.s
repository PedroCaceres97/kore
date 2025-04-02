; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kmemcmp

; rax = (return)    bool
; rdi = (1st)       const char*     src
; rsi = (2nd)       const char*     dst
; rdx = (3rd)       size_t          count
asm_kmemcmp:
    cmp     rdx, 0
    je      .equal

    cmp     rdx, 8
    jb      .unaligned_compare

    mov     r10, rdi
    mov     r11, rsi
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_compare:
    mov     r10b, [rdi]
    mov     r11b, [rsi]
    cmp     r10b, r11b
    jne     .nequal

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

    dec     rdx
    jz      .equal

    inc     rdi
    inc     rsi
    jmp     .align

.aligned_compare:
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

.nequal:
    mov     rax, 0
    ret

.equal:
    mov     rax, 1
    ret