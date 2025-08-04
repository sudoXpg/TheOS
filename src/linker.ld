ENTRY(_start)
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 1M;
/* 
    4096 assures that the section starts at a new page wrt the paging model
    essentially matches the hardware page size 
*/
    .text : ALIGN(4096)
    {
        *(.text)
    }
    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }
    .data : ALIGN(4096)
    {
        *(.data)
    }
    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }
    .asm : ALIGN(4096)
    {
        *(.asm)
    }

}