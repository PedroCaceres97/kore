; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kmemcpy

; rax = (return) void
; rcx =    (1st) const char*    dst
; rdx =    (2nd) const char*    src
; r8  =    (3rd) size_t         count
kmemcpy:
    test    r8, r8
    jz      .done

    cmp     r8, 8
    jb      .unaligned_copy

    mov     r10, rcx
    mov     r11, rdx
    and     r10, 7
    and     r11, 7
    cmp     r10, r11
    je      .align

.unaligned_copy:
    mov     r10b, [rdx]
    mov     [rcx], r10b

    inc     rcx
    inc     rdx

    dec     r8
    jz      .done
    jmp     .unaligned_copy

.align:
    test    rcx, 7
    jz      .aligned_copy

    mov     r10b, [rdx]
    mov     [rcx], r10b

    inc     rcx
    inc     rdx

    dec     r8
    jz      .done
    jmp     .align

.aligned_copy:
    mov     r10, [rdx]
    mov     [rcx], r10

    add     rcx, 8
    add     rdx, 8
    sub     r8, 8
    jz      .done

    cmp     r8, 8
    jb      .unaligned_copy

.done:
    ret