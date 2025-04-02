; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kmemcpy

; rax = (return)    void
; rdi = (1st)       char*           dst
; rsi = (2nd)       const char*     src
; rdx = (3rd)       size_t          count
asm_kmemcpy:
    test    rdx, rdx
    jz      .done

    cmp     rdx, 8
    jb      .unaligned_copy

    mov     r10, rdi
    mov     r11, rsi
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_copy:
    mov     r10b, [rsi]
    mov     [rdi], r10b

    inc     rdi
    inc     rsi

    dec     rdx
    jz      .done
    jmp     .unaligned_copy

.align:
    test    rdi, 7
    jz      .aligned_copy

    mov     r10b, [rsi]
    mov     [rdi], r10b

    inc     rdi
    inc     rsi

    dec     rdx
    jz      .done
    jmp     .align

.aligned_copy:
    mov     r10, [rsi]
    mov     [rdi], r10

    add     rdi, 8
    add     rsi, 8
    sub     rdx, 8
    jz      .done

    cmp     rdx, 8
    jb      .unaligned_copy

.done:
    ret