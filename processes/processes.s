.intel_syntax noprefix
.align 32

.global _get_eip
_get_eip:
    pop eax
    push eax
    ret

.global _process_springboard
_process_springboard:
    mov ecx, [esp+4]
    mov ebp, [esp+8]
    mov esp, [esp+12]
    xor eax, eax
    jmp ecx

.extern switch_process
.global _yield
_yield:
    cli
    pusha
    call switch_process;
    popa
    sti
    ret
