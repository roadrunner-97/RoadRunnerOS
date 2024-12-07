ENTRY(_start)
SECTIONS
{
	. = 1M;
	_kernel_start = ALIGN(8);
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
_kernel_end = ALIGN(8);
_kernel_size = _kernel_end - _kernel_start;
