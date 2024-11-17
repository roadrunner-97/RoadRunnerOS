.intel_syntax noprefix
.align 32

.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31


_isr0:
    cli
    push 0x00 /* Dummy value used to keep the stack frame at a constant size */
    push 0x00 /* this is just the isr number */
    jmp isr_handler_common

_isr1:
    cli
    push 0x00
    push 0x01
    jmp isr_handler_common

_isr2:
    cli
    push 0x00
    push 0x02
    jmp isr_handler_common

_isr3:
    cli
    push 0x00
    push 0x03
    jmp isr_handler_common

_isr4:
    cli
    push 0x00
    push 0x04
    jmp isr_handler_common

_isr5:
    cli
    push 0x00
    push 0x05
    jmp isr_handler_common

_isr6:
    cli
    push 0x00
    push 0x06
    jmp isr_handler_common

_isr7:
    cli
    push 0x00
    push 0x07
    jmp isr_handler_common

_isr8: /* double fault exception */
    cli
    push 0x08 /* no dummy here because this one already has a value pushed on the stack */

_isr9:
    cli
    push 0x00
    push 0x09
    jmp isr_handler_common

_isr10:
    cli
    push 0x0A /* no dummy here because this one already has a value pushed on the stack */

_isr11:
    cli
    push 0x0B /* no dummy here because this one already has a value pushed on the stack */

_isr12:
    cli
    push 0x0C /* no dummy here because this one already has a value pushed on the stack */

_isr13:
    cli
    push 0x0D /* no dummy here because this one already has a value pushed on the stack */

_isr14:
    cli
    push 0x0E /* no dummy here because this one already has a value pushed on the stack */

_isr15:
    cli
    push 0x00
    push 0x0F
    jmp isr_handler_common

_isr16:
    cli
    push 0x00
    push 0x10
    jmp isr_handler_common

_isr17:
    cli
    push 0x00
    push 0x11
    jmp isr_handler_common

_isr18:
    cli
    push 0x00
    push 0x12
    jmp isr_handler_common

_isr19:
    cli
    push 0x00
    push 0x13
    jmp isr_handler_common

_isr20:
    cli
    push 0x00
    push 0x14
    jmp isr_handler_common

_isr21:
    cli
    push 0x00
    push 0x15
    jmp isr_handler_common

_isr22:
    cli
    push 0x00
    push 0x16
    jmp isr_handler_common

_isr23:
    cli
    push 0x00
    push 0x17
    jmp isr_handler_common

_isr24:
    cli
    push 0x00
    push 0x18
    jmp isr_handler_common

_isr25:
    cli
    push 0x00
    push 0x19
    jmp isr_handler_common

_isr26:
    cli
    push 0x00
    push 0x1A
    jmp isr_handler_common

_isr27:
    cli
    push 0x00
    push 0x1B
    jmp isr_handler_common

_isr28:
    cli
    push 0x00
    push 0x1C
    jmp isr_handler_common

_isr29:
    cli
    push 0x00
    push 0x1D
    jmp isr_handler_common

_isr30:
    cli
    push 0x00
    push 0x1E
    jmp isr_handler_common

_isr31:
    cli
    push 0x00
    push 0x1F
    jmp isr_handler_common

.extern _fault_handler /* we will write that in C */

isr_handler_common: /* this is what we're calling with all the ISRs */
    pusha

    push ds
    push es
    push fs
    push gs /* preserve the state of the GDT registers because we necessarily need to be in kernel mode to handle the ISR */

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax /* now our data segments are all kernel mode */

    mov eax, esp
    push eax
    call _fault_handler /* jump to the C code for the fault handler */

    pop eax
    pop gs
    pop fs
    pop es
    pop ds

    popa /* unwind all the shit we just did */
    add esp, 8 /* dump the two items we added to the stack for the dummy byte and the ISR number */
    iret /* GET OUTTA HERE! */
