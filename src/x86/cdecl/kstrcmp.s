; Architecture: x86_64
; Microsoft x64 Calling Convention

section .text
global kstrcmp

kstrcmp:
    xor     eax, eax        ; eax = 0
    push    
    mov     r8, rcx         ; r8 = rcx
    mov     r9, rdx         ; r9 = rdx
    and     r8, 7           ; r8 = r8 % 8
    and     r9, 7           ; r9 = r9 % 8
    cmp     r8, r9      
    je      .align_loop     ; if r8 == r9 

.unaligned_loop:
    mov     r8b, [rcx]      ; r8b = *rcx
    mov     r9b, [rdx]      ; r9b = *rdx
    cmp     r8b, r9b    
    jne     .nequal         ; if r8b != r9b

    test    r8b, r8b    
    jz      .equal          ; if r8b == 0

    inc     rcx             ; rcx++
    inc     rdx             ; rdx++
    jmp     .unaligned_loop

.align_loop:
    test    rcx, 7      
    jz      .aligned_loop   ; if rcx % 8 == 0

    mov     r8b, [rcx]      ; r8b = *rcx
    mov     r9b, [rdx]      ; r9b = *rdx
    cmp     r8b, r9b    
    jne     .nequal         ; if r8b != r9b

    test    r8b, r8b        
    jz      .equal          ; if r8b == 0

    inc     rcx             ; rcx++
    inc     rdx             ; rdx++
    jmp     .align_loop

.aligned_loop:
    mov     r8, [rcx]       ; r8 = *rcx
    mov     r9, [rdx]       ; r9 = *rcx

    mov     r10, r8         ; r10 = r8
    call    any_zero
    jnz     .byte_loop      ; if any 0 in r8 compare byte to byte

    mov     r10, r9
    call    any_zero
    jnz     .byte_loop      ; if any 0 in r9 compare byte to byte

    cmp     r8, r9      
    jne     .nequal         ; if r8 != r9

    add     rcx, 8          ; rcx += 8
    add     rdx, 8          ; rdx += 8 
    jmp     .aligned_loop

.byte_loop:
    mov     r8b, [rcx]      ; r8b = *rcx
    mov     r9b, [rdx]      ; r9b = *rdx
    cmp     r8b, r9b        ; if r8b != r9b
    jne     .nequal         

    test    r8b, r8b
    jz      .equal          ; if r8b == 0

    inc     rcx             ; rcx++
    inc     rdx             ; rdx++
    test    rcx, 7  
    jnz     .byte_loop      ; if rcx % 8 != 0

.equal:
    mov eax, 1
    ret

.nequal:
    mov eax, 0
    ret

; r10 = bytes
; r11 (override)
any_zero:
    mov     r11, r10
    sub     r11, 0x0101010101010101
    not     r10                    
    and     r10, r11                
    and     r10, 0x8080808080808080
    ret