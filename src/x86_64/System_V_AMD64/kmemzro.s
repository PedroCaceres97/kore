; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kmemzro

; rax  = (return)    void
; rdi  = (1st)       char*           dst
; rsi  = (2nd)       size_t          count
asm_kmemzro:
    test    rsi, rsi
    jz      .done

    mov     rdx, 0

    cmp     rsi, 8
    jb      .unaligned_set

    test    rdi, 7
    jz      .aligned_set

.align:
    mov     [rdi], dil
    inc     rdi
    dec     rsi
    jz      .done

    cmp     rsi, 8
    jb      .unaligned_set

    test    rdi, 7
    jnz     .align

.aligned_set:
    mov     [rdi], rdx

    add     rdi, 8
    sub     rsi, 8
    jz      .done 
    
    cmp     rsi, 8
    jg      .aligned_set

.unaligned_set:
    mov     [rdi], dil
    inc     rdi
    dec     rsi
    jnz     .unaligned_set

.done:
    ret