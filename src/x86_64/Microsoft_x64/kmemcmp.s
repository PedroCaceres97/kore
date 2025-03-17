; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kmemcmp

; rax = (return) bool
; rcx =    (1st) const char*    src
; rdx =    (2nd) const char*    dst
; r8  =    (3rd) size_t         count
kmemcmp:
    cmp     r8, 0
    je      .equal

    cmp     r8, 8
    jb      .unaligned_compare

    mov     r10, rcx
    mov     r11, rdx
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_compare:
    mov     r10b, [rcx]
    mov     r11b, [rdx]
    cmp     r10b, r11b
    jne     .nequal

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

    dec     r8
    jz      .equal

    inc     rcx
    inc     rdx
    jmp     .align

.aligned_compare:
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

.nequal:
    mov     rax, 0
    ret

.equal:
    mov     rax, 1
    ret