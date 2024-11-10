.intel_syntax noprefix
.global _gdt_set_asm /* function will exist in C land as gdt_flush i think */
.extern pws_gdt /* this is the pointer with size */
_gdt_set_asm:
    lgdt [pws_gdt] /* this is making the CPU aware that there's a GDT at the address in pws_gdt */
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush2
.flush2:
    ret

.global _idt_set_asm
.extern pws_idt
_idt_set_asm:    lidt [pws_idt]
    ret
