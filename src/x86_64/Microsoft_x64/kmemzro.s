; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global asm_kmemset

; rax = (return)    void
; rcx = (1st)       const char*     dst
; rdx  = (2nd)      size_t          count
asm_kmemset:
    test    rdx, rdx
    jz      .done

    mov     r8, 0

    cmp     rdx, 8
    jb      .unaligned_set

    test    rcx, 7
    jz      .aligned_set

.align:
    mov     [rcx], r8b
    inc     rcx
    dec     rdx
    jz      .done

    cmp     rdx, 8
    jb      .unaligned_set

    test    rcx, 7
    jnz     .align

.aligned_set:
    mov     [rcx], r8

    add     rcx, 8
    sub     rdx, 8
    jz      .done 
    
    cmp     rdx, 8
    jg      .aligned_set

.unaligned_set:
    mov     [rcx], r8b
    inc     rcx
    dec     rdx
    jnz     .unaligned_set

.done:
    ret