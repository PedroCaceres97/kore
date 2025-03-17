; Architecture: x86
; cdecl Convention

section .text
global kstrlen

kstrlen:
    mov     edx, [esp + 4]
    push    edi
    push    esi
    mov     edi, edx
    xor     edx, edx            
    xor     eax, eax            

.align_loop:
    mov     esi, edi            
    add     esi, eax            
    test    esi, 3              
    jz      .loop               

    mov     dl, [esi]           
    test    dl, dl              
    jz      .done               
    inc     eax                 
    jmp     .align_loop

.loop:
    mov     esi, edi            
    add     esi, eax            
    mov     edx, [esi]          
    mov     ecx, edx            

    sub     ecx, 0x01010101     
    not     edx                 
    and     edx, ecx            
    and     edx, 0x80808080     
    jnz     .byte_search        

    add     eax, 4              
    jmp     .loop

.byte_search:
    xor     edx, edx            

.byte_loop:
    mov     esi, edi            
    add     esi, eax            
    mov     dl, [esi + edx]     
    test    dl, dl              
    jz      .byte_end           
    inc     edx                 
    cmp     edx, 4              
    jne     .byte_loop

.byte_end:
    add     eax, edx            

.done:
    pop esi
    pop edi
    ret