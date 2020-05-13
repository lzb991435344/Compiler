#include "interrupts.h"


//lesson 06

// http://www.lowlevel.eu/wiki/Tyndur
// make interrupts.o
// nm interrupts.o 
/**nm interrupts.o 
      U _GLOBAL_OFFSET_TABLE_
00000000 T __x86.get_pc_thunk.ax
         U _Z6printfPc
00000000 T _ZN16InterruptManager16handlerInterruptEhj  //name esp


*/

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

 void InterruptManager::setInterruptDescriptorTableEntry(
		uint8_t interruptNumber,
		uint16_t gdt_codeSegmentSelectorOffset,
		void (*handler) (),
		uint8_t DescriptorPrivilegeLevel,
		uint8_t DescriptorType){

 	const  uint8_t IDT_DESC_PRESENT = 0x80;

 	interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
 	interruptDescriptorTable[interruptNumber].handlerAddressHighBits = ((uint32_t)handler >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = gdt_codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel & 3) << 5); 
    interruptDescriptorTable[interruptNumber].reserved = 0;
}


InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
:picMasterCommand(0x20),
picMasterData(0x21),
picSlaveCommand(0xA0),
picSlaveData(0xA1)
{
	uint32_t CodeSegment = gdt->CodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xE;

	for(uint16_t i = 0; i < 256; ++i){
		setInterruptDescriptorTableEntry(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}

	setInterruptDescriptorTableEntry(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

	picMasterCommand.Write(0x11);
	picSlaveCommand.Write(0x11);

	picMasterData.Write(0x20);
	picSlaveData.Write(0x28);//why?20-27  28-30

	picMasterData.Write(0x04);
	picSlaveData.Write(0x02);//why?20-27  28-30

	picMasterData.Write(0x01);
	picSlaveData.Write(0x01);//why?20-27  28-30

	picMasterData.Write(0x00);
	picSlaveData.Write(0x00);//why?20-27  28-30

	InterruptDescriptorTablePointer idt;
	idt.size = 256 *sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t) interruptDescriptorTable;


	asm volatile("lidt %0" : : "m" (idt));

}

InterruptManager::~InterruptManager(){

}


void InterruptManager::Active(){

}

uint32_t InterruptManager::handlerInterrupt(uint8_t interruptNumber, uint32_t esp){

	printf("INTERRUPT");
	return esp;
}

void InterruptManager::HandleInterruptRequest0x00(){

}
 void InterruptManager::HandleInterruptRequest0x01(){

}
