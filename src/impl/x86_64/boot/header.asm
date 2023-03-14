section .multiboot_header
header_start:						;Multiboot2 header (https://tinyurl.com/mwhf32zf)
	dd 0xE85250D6					;Magic number
	dd 0							;Protected mode i386
	dd header_end - header_start	;Header len
	dd 0x100000000 - (0xE85250D6 + 0 +  (header_end - header_start))	;Checksum

	dw 0
	dw 0
	dd 8
header_end:
