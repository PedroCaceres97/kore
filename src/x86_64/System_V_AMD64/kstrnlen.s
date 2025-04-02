; Architecture: x86_64
; System V AMD64 Calling Convention

section .text
global asm_kstrnlen

; rax = (return)    size_t
; rdi = (1st)       const char*     src
; rsi = (2nd)       size_t          count

asm_kstrnlen:        
    push    r12
    push    r13
    mov     r12, 0x0101010101010101
    mov     r13, 0x8080808080808080

    mov     rax, rdi

    test    rsi, rsi
    jz      .done    

    cmp     rsi, 8
    jb      .unaligned_loop

.align:
    test    rdi, 7              
    jz      .aligned_loop           

    mov     r10b, [rdi]           
    test    r10b, r10b              
    jz      .done

    dec     rsi
    jz      .done

    inc     rdi
    jmp     .align

.aligned_loop:
    mov     r10, [rdi]             
    mov     r11, r10
    sub     r11, r12
    not     r10                    
    and     r10, r11                
    and     r10, r13
    jnz     .unaligned_loop

    add     rdi, 8
    sub     rsi, 8
    jz      .done

    cmp     rsi, 8
    jb      .unaligned_loop
    jmp     .aligned_loop 

.unaligned_loop:
    mov     r10b, [rdi]           
    test    r10b, r10b              
    jz      .done

    dec     rsi
    jz      .done

    inc     rdi
    jmp     .unaligned_loop

.done:
    pop r13
    pop r12
    sub     rdi, rax
    mov     rax, rdi
    ret