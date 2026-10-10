.intel_syntax noprefix
.align 32
.code32

# needed because we update the page directory in a critical path
.extern page_directory

.global _get_eip
_get_eip:
    pop eax
    push eax
    ret

.global _process_springboard
_process_springboard:
    cli
    mov ecx, [esp+4]
    mov ebp, [esp+8]
    mov eax, [esp+12]
    mov ebx, [esp+16]
    mov edx, [esp+20]

    mov [page_directory], ebx #order not really critical since interrupts disabled
    mov cr3, ebx
    mov esp, eax
    xor eax, eax

    cmp dl, 0
    je .resume
    sti

.resume:
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
