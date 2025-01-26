.intel_syntax noprefix
.align 32
.code32

.global _irq0
.global _irq1
.global _irq2
.global _irq3
.global _irq4
.global _irq5
.global _irq6
.global _irq7
.global _irq8
.global _irq9
.global _irq10
.global _irq11
.global _irq12
.global _irq13
.global _irq14
.global _irq15

_irq0:
    cli
    push  0;
    push 32; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq1:
    cli
    push  0;
    push 33; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq2:
    cli
    push  0;
    push 34; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq3:
    cli
    push  0;
    push 35; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq4:
    cli
    push  0;
    push 36; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq5:
    cli
    push  0;
    push 37; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq6:
    cli
    push  0;
    push 38; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq7:
    cli
    push  0;
    push 39; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq8:
    cli
    push  0;
    push 40; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq9:
    cli
    push  0;
    push 41; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq10:
    cli
    push  0;
    push 42; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq11:
    cli
    push  0;
    push 43; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq12:
    cli
    push  0;
    push 44; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq13:
    cli
    push  0;
    push 45; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq14:
    cli
    push  0;
    push 46; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub

_irq15:
    cli
    push  0;
    push 47; /* the IRQs will be set to run using ISRs 32-47 */
    jmp irq_common_stub


.extern _irq_handler;

irq_common_stub: /*all the common IRQ handlers call this */
    pusha

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push eax
    call _irq_handler

    pop eax
    pop gs
    pop fs
    pop es
    pop ds

    popa
    add esp, 8
    iret
