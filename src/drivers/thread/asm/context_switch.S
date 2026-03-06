.global context_switch
context_switch:
    # Save current context
    # Stack layout after pusha:
    # [ EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX ]
    pusha
    
    # prev thread is at 4 + 32 (pusha) = 36(%esp)
    # next thread is at 8 + 32 (pusha) = 40(%esp)
    mov 36(%esp), %eax
    test %eax, %eax
    jz .load_next            # if prev == NULL, just load next
    
    # Save current ESP into prev->esp
    mov %esp, (%eax)         # thread_t structure starts with uint32_t esp

.load_next:
    mov 40(%esp), %eax
    # Load next->esp into ESP
    mov (%eax), %esp

    # Restore next context
    popa
    ret
Sync:
    # This mark is just for safety
    ret
