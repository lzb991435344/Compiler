//#include "port.h"

#include <hardwarecommunication/port.h>

using namespace myos::common;
//using namespace myos::drivers;
using namespace myos::hardwarecommunication;


Port::Port(myos::common::uint16_t portnumber){
	this->portnumber = portnumber;
}

Port::~Port(){

}


Port8Bit::Port8Bit(myos::common::uint16_t portnumber)
:Port(portnumber){
	
}

Port8Bit::~Port8Bit(){

}

/**	
void Port8Bit::Write(uint8_t data){
	__asm__ volatile("outb %0, %1" :: "a"(data), "Nd"(portnumber));
}

uint8_t Port8Bit::Read(){
	uint8_t result;
	__asm__ volatile("inb %0, %1" :: "=a"(result), "Nd"(portnumber));
	return result;
}
*/

//
Port8BitSlow::Port8BitSlow(myos::common::uint16_t portnumber)
:Port8Bit(portnumber){

}

Port8BitSlow::~Port8BitSlow(){

}
	
void Port8BitSlow::Write(myos::common::uint8_t data){
	Write8(portnumber, data);
}
myos::common::uint8_t Port8BitSlow::Read(){
	return Read8(portnumber);
}




Port16Bit::Port16Bit(myos::common::uint16_t portnumber)
:Port(portnumber){

}
Port16Bit::~Port16Bit(){

}
	
void Port16Bit::Write(myos::common::uint16_t data){
	Write16(portnumber, data);
}
myos::common::uint16_t Port16Bit::Read(){
	return Read16(portnumber);
}


Port32Bit::Port32Bit(uint16_t portnumber)
:Port(portnumber){

}

Port32Bit::~Port32Bit(){

}
	
void Port32Bit::Write(uint32_t data){
	Write32(portnumber, data);
}

myos::common::uint32_t Port32Bit::Read(){
	return Read32(portnumber);
}