#include "keyboard.h"
#include "types.h"
#include "interrupts.h"
#include "gdt.h"

void printf(char* str);

keyboardDriver::keyboardDriver(InterruptManager* manage)
:InterruptHandler(0x21, manage),
dataport(0x60),
commandport(0x64)
{

 while(commandport.Read() & 0x1){
 	dataport.Read();
 }
 commandport.Write(0xAE); //activate interrupt
 commandport.Write(0x20); //get current stay

 uint8_t status = (dataport.Read() | 1) & ~0x10;
 commandport.Write(0x60); //set state
 dataport.Write(status);

 dataport.Write(0xF4);


}
keyboardDriver::~keyboardDriver(){

}

uint32_t keyboardDriver::HandleInterrupt(uint32_t esp){
	uint8_t key = dataport.Read();
	char* foo = "KEYBOARD 0x00";
	char* hex = "0123456789ABCDEF";
	foo[22] = hex[(key >> 4) & 0x0F];
	foo[23] = hex[key & 0x0F];
	printf(foo);

	return esp;
}