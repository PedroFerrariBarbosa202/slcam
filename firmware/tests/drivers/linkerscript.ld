/*
 * STM32F103 linker script
 *
 * Flash: 64 KB  @ 0x08000000
 * SRAM:  20 KB  @ 0x20000000
 */

/* Define memory regions. */
MEMORY
{
	rom (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Enforce emission of the vector table. */
EXTERN(vector_table)

/* Define the entry point of the output file. */
ENTRY(reset_handler)

/* Define sections. */
SECTIONS
{
	.text : {
		*(.vectors)	/* Vector table */
		*(.text*)	/* Program code */
		. = ALIGN(4);
		*(.rodata*)	/* Read-only data */
		. = ALIGN(4);
	} >rom

	/* C++ static constructors/destructors */
	.preinit_array : {
		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP(*(.preinit_array))
		__preinit_array_end = .;
	} >rom

	.init_array : {
		. = ALIGN(4);
		__init_array_start = .;
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		__init_array_end = .;
	} >rom

	.fini_array : {
		. = ALIGN(4);
		__fini_array_start = .;
		KEEP(*(.fini_array))
		KEEP(*(SORT(.fini_array.*)))
		__fini_array_end = .;
	} >rom

	.ARM.extab : {
		*(.ARM.extab*)
	} >rom

	.ARM.exidx : {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	} >rom

	. = ALIGN(4);
	_etext = .;

	/* RAM not initialized/cleared on reset */
	.noinit (NOLOAD) : {
		*(.noinit*)
	} >ram

	. = ALIGN(4);

	/* Initialized data */
	.data : {
		_data = .;
		*(.data*)
		*(.ramtext*)
		. = ALIGN(4);
		_edata = .;
	} >ram AT >rom

	_data_loadaddr = LOADADDR(.data);

	/* Zero-initialized data */
	.bss : {
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} >ram

	/* C++ exception handling -- normally unused in bare metal */
	/DISCARD/ : {
		*(.eh_frame)
	}

	. = ALIGN(4);
	end = .;
}

/* Top of stack */
PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
