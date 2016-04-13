/*
 * STM32F7 discovery memory map - GNU ld linker script file
 */

MEMORY
{
    rom          :   ORIGIN = 0x08000000, LENGTH = 1024K
    ram          :   ORIGIN = 0x20000000, LENGTH = 320K
}

/* Include main link script. Note: it will be searched in -L paths. */
/* INCLUDE sections.ld*/
INCLUDE cortexm_base.ld

