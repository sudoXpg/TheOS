#include "idt.h"

struct InterruptDescriptor32 IDT_desc[THEOS_MAX_INTS];
struct idtr_desc idtr;


extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrupt();

void int21h_handler(){
    print("\nKey pressed\n");
    out_byte(0x20, 0x20); //End of Interrupt (EOI) signal
}

void no_interrupt_handler(){
    out_byte(0x20, 0x20); // End of Interrupt (EOI) signal
}

void idt_zero(){
    print("\nDIV BY ZERO\n");
    for(;;);
}

void idt_set(uint32_t int_num, void *int_addr){
    struct InterruptDescriptor32 *idt_entry = &IDT_desc[int_num];
    idt_entry->offset_1 = (uint32_t) int_addr & 0x0000FFFF;
    idt_entry->offset_2 = (uint32_t)int_addr >> 16;
    idt_entry->selector = KER_CODE_SEG;
    idt_entry->zero = 0;
    idt_entry->type_attributes = 0x8E ; // 32-bit Trap Gate   
}

void idt_init(){
    uint32_t size_IDT = sizeof(IDT_desc);
    memset(IDT_desc, 0, size_IDT);
    idtr.limit = size_IDT-1;
    idtr.base = (uint32_t) IDT_desc;

    for (int i = 0; i < THEOS_MAX_INTS; i++){
        idt_set(i, no_interrupt);
    }

    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    idt_load(&idtr);
}