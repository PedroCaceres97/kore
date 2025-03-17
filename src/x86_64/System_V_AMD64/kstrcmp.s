; Architecture: x86_64
; System V AMD64 ABI (Unix-like Systems)

section .text
global kstrcmp

kstrcmp:
    xor     rax, rax        ; rax = 0
    mov     r8, rdi         ; r8 = rdi
    mov     r9, rsi         ; r9 = rsi
    and     r8, 7           ; r8 = r8 % 8
    and     r9, 7           ; r9 = r9 % 8
    cmp     r8, r9      
    je      .align_loop     ; if r8 == r9 

.unaligned_loop:
    mov     r8b, [rdi]      ; r8b = *rdi
    mov     r9b, [rsi]      ; r9b = *rsi
    cmp     r8b, r9b    
    jne     .nequal         ; if r8b != r9b

    test    r8b, r8b    
    jz      .equal          ; if r8b == 0

    inc     rdi             ; rdi++
    inc     rsi             ; rsi++
    jmp     .unaligned_loop

.align_loop:
    test    rdi, 7      
    jz      .aligned_loop   ; if rdi % 8 == 0

    mov     r8b, [rdi]      ; r8b = *rdi
    mov     r9b, [rsi]      ; r9b = *rsi
    cmp     r8b, r9b    
    jne     .nequal         ; if r8b != r9b

    test    r8b, r8b        
    jz      .equal          ; if r8b == 0

    inc     rdi             ; rdi++
    inc     rsi             ; rsi++
    jmp     .align_loop

.aligned_loop:
    mov     r8, [rdi]       ; r8 = *rdi
    mov     r9, [rsi]       ; r9 = *rdi

    mov     r10, r8         ; r10 = r8
    mov     r11, r10
    sub     r11, 0x0101010101010101
    not     r10                    
    and     r10, r11                
    and     r10, 0x8080808080808080
    jnz     .byte_loop      ; if any 0 in r8 compare byte to byte

    mov     r10, r9
    mov     r11, r10
    sub     r11, 0x0101010101010101
    not     r10                    
    and     r10, r11                
    and     r10, 0x8080808080808080
    jnz     .byte_loop      ; if any 0 in r9 compare byte to byte

    cmp     r8, r9      
    jne     .nequal         ; if r8 != r9

    add     rdi, 8          ; rdi += 8
    add     rsi, 8          ; rsi += 8 
    jmp     .aligned_loop

.byte_loop:
    mov     r8b, [rdi]      ; r8b = *rdi
    mov     r9b, [rsi]      ; r9b = *rsi
    cmp     r8b, r9b        ; if r8b != r9b
    jne     .nequal         

    test    r8b, r8b
    jz      .equal          ; if r8b == 0

    inc     rdi             ; rdi++
    inc     rsi             ; rsi++
    test    rdi, 7  
    jnz     .byte_loop      ; if rdi % 8 != 0

.equal:
    mov eax, 1
    ret

.nequal:
    mov eax, 0
    ret