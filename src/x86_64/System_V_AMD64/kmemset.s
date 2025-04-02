; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kmemset

; rax  = (return)    void
; rdi  = (1st)       char*           dst
; sil  = (2nd)       unsigned char   value
; rdx  = (3rd)       size_t          count
asm_kmemset:
    test    rdx, rdx
    jz      .done

    mov     rax, 0x0101010101010101
    mul     rsi
    mov     rsi, rax

    cmp     rdx, 8
    jb      .unaligned_set

    test    rdi, 7
    jz      .aligned_set

.align:
    mov     [rdi], sil
    inc     rdi
    dec     rdx
    jz      .done

    cmp     rdx, 8
    jb      .unaligned_set

    test    rdi, 7
    jnz     .align

.aligned_set:
    mov     [rdi], rsi

    add     rdi, 8
    sub     rdx, 8
    jz      .done 
    
    cmp     rdx, 8
    jg      .aligned_set

.unaligned_set:
    mov     [rdi], sil
    inc     rdi
    dec     rdx
    jnz     .unaligned_set

.done:
    ret