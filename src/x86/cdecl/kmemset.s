; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kmemset

; rax = (return) void
; rcx =    (1st) const char*    dst
; dl  =    (2nd) unsigned char  value
; r8  =    (3rd) size_t         count
kmemset:
    test    r8, r8
    jz      .done

    mov     rax, 0x0101010101010101
    mul     rdx
    mov     rdx, rax

    cmp     r8, 8
    jb      .unaligned_set

    test    rcx, 7
    jz      .aligned_set

.align:
    mov     [rcx], dl
    inc     rcx
    dec     r8
    jz      .done

    cmp     r8, 8
    jb      .unaligned_set

    test    rcx, 7
    jnz     .align

.aligned_set:
    mov     [rcx], rdx

    add     rcx, 8
    sub     r8, 8
    jz      .done 
    
    cmp     r8, 8
    jg      .aligned_set

.unaligned_set:
    mov     [rcx], dl
    inc     rcx
    dec     r8
    jnz     .unaligned_set

.done:
    ret