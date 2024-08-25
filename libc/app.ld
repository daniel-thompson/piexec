MEMORY
{
	RAM (rwx) : ORIGIN = 0x01000000, LENGTH = 520K
}

ENTRY(_start)

SECTIONS
{
	.text :
	{
	        *(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
	} >RAM

	.data :
	{
		*(.data)
		. = ALIGN(4);
	} >RAM

	.bss :
	{
		*(.bss)
		. = ALIGN(4);
	} >RAM
}
