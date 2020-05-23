//#include "interrupts.h"
#include <hardwarecommunication/interrupts.h>


using namespace myos;
using namespace myos::common;
//using namespace myos::drivers;
using namespace myos::hardwarecommunication;

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
void printfHex(uint8_t);

InterruptHandler::InterruptHandler(uint8_t interruptNumber, InterruptManager* interruptManager){
	this->interruptNumber = interruptNumber;
	this->interruptManager = interruptManager;
	interruptManager->handlers[interruptNumber] = this;

}
InterruptHandler::~InterruptHandler(){
	if(interruptManager->handlers[interruptNumber] == this){
		interruptManager->handlers[interruptNumber] = 0;
	}
}


uint32_t InterruptHandler::handlerInterrupt(uint32_t esp){

	return esp;
}



InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

InterruptManager* InterruptManager::ActiveInterruptManager = 0;

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


InterruptManager::InterruptManager(myos::common::uint16_t hardwareInterruptOffset,  myos::GlobalDescriptorTable* globalDescriptorTable,
	TaskManager* taskManager)
:programInterruptControllerMasterCommand(0x20),
programInterruptControllerMasterData(0x21),
programInterruptControllerSlaveCommand(0xA0),
programInterruptControllerSlaveData(0xA1)
{
	this->taskManager = taskManager;
	this->HardwareInterruptOffset = hardwareInterruptOffset;
	uint32_t CodeSegment = globalDescriptorTable->CodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xE;

	for(uint16_t i = 255; i > 0; --i){
		handlers[i] = 0;
		setInterruptDescriptorTableEntry(i, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
	}

	
	setInterruptDescriptorTableEntry(0, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
	handlers[0] = 0;

	setInterruptDescriptorTableEntry(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x01, CodeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x02, CodeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x03, CodeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x04, CodeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x05, CodeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x06, CodeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x07, CodeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x08, CodeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x09, CodeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0A, CodeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0B, CodeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0C, CodeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0D, CodeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0E, CodeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x0F, CodeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x10, CodeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x11, CodeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x12, CodeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(0x13, CodeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);


	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, CodeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, CodeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, CodeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, CodeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, CodeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, CodeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, CodeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, CodeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, CodeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, CodeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, CodeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, CodeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
	setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, CodeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);



	programInterruptControllerMasterCommand.Write(0x11);
	programInterruptControllerSlaveCommand.Write(0x11);

	programInterruptControllerMasterData.Write(0x20);
	programInterruptControllerSlaveData.Write(0x28);//why?20-27  28-30

	programInterruptControllerMasterData.Write(0x04);
	programInterruptControllerSlaveData.Write(0x02);//why?20-27  28-30

	programInterruptControllerMasterData.Write(0x01);
	programInterruptControllerSlaveData.Write(0x01);//why?20-27  28-30

	programInterruptControllerMasterData.Write(0x00);
	programInterruptControllerSlaveData.Write(0x00);//why?20-27  28-30

	InterruptDescriptorTablePointer idt;
	idt.size = 256 *sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t) interruptDescriptorTable;


	asm volatile("lidt %0" : : "m" (idt));

}

InterruptManager::~InterruptManager(){

}

//lesson07
void InterruptManager::Activate(){

	if(ActiveInterruptManager != 0){
		ActiveInterruptManager->Deactivate();
	}

	ActiveInterruptManager = this;
	asm("sti");
}

void InterruptManager::Deactivate(){

	if(ActiveInterruptManager == this){
		ActiveInterruptManager = 0;
		asm("cli");
	}	
}

//lesson07
uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp){

	if(ActiveInterruptManager != 0){
		return ActiveInterruptManager->DoHandlerInterrupt(interruptNumber, esp);
	}
	//printf("INTERRUPT");
	return esp;
}

//lesson07
uint32_t InterruptManager::DoHandlerInterrupt(uint8_t interruptNumber, uint32_t esp){

	if(handlers[interruptNumber] != 0){
		esp = handlers[interruptNumber]->handlerInterrupt(esp);
	}//else if(interruptNumber != 0x20){
	else if(interruptNumber != HardwareInterruptOffset){
		printf("UNHANDLER INTERRUPT 0x");
		printfHex(interruptNumber);
		/*char* hex = "0123456789ABCDEF";
		foo[22] = hex[(interruptNumber >> 4) & 0x0F];
		foo[23] = hex[interruptNumber & 0x0F];
		printf(foo);*/
	}

	//set esp
	if(interruptNumber == HardwareInterruptOffset){
		esp = (uint32_t)taskManager->Schedule((CPUState*) esp);
	}
	
	/*if(ActiveInterruptManager != 0){
		return ActiveInterruptManager->DoHandlerInterrupt(interruptNumber, esp);
	}*/
	
	if(0x20 <= interruptNumber && interruptNumber < 0x30){
		
		programInterruptControllerMasterCommand.Write(0x20);

		if(0x28 <= interruptNumber ){
			programInterruptControllerSlaveCommand.Write(0x20);
		}
	}

	return esp;
}

void InterruptManager::HandleInterruptRequest0x00(){

}
 void InterruptManager::HandleInterruptRequest0x01(){

}
