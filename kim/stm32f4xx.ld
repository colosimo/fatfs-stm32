/* Warning: linker script valid for flash boot only */
SECTIONS
{
	.text 0x08000000: {
		*(isrv_sys); /* Interrupt Service Routine Vector - System */
		*(isrv_irq); /* Interrupt Service Routine Vector - Peripherals IRQs */
		. = 0x00000400;
		*(.text.romboot)
		*(.text)
	}

	. = ALIGN(16);
	.etext = .;

	.rodata : {
		*(.rodata)
	}

	. = ALIGN(16);
	_erom = .;

	.data 0x20000000: AT (_erom) {
		_sdata_flash = LOADADDR(.data);
		_sdata = .;
		*(.data);
	}
	_edata = .;

	.bss : {
		. = ALIGN(16);
		_sbss = .;
		*(.bss);
		. = ALIGN(16);
		_ebss = .;
	}
}
