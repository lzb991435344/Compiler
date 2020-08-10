#include <syscalls.h>

using namespace myos;
using namespace myos::common;

void printf(char*);
void printfHex(uint8_t);



SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:InterruptHandler(InterruptNumber  + interruptManager->HardwareInterruptOffset() ,interruptManager){

}

SyscallHandler::~SyscallHandler(){

}
		
//21 22
uint32_t SyscallHandler::HandleInterrupt(uint32_t esp){
	CPUState* cpu = (CPUState*)esp;

	switch(cpu->eax){
		case 4:
			printf((char*)cpu->ebx);
		break;


		default:
		break;
	}
}



