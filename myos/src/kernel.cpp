//#include "types.h"
//#include "gdt.h"
//#include "interrupts.h"
//#include "keyboard.h"
//#include "driver.h"
//#include "mouse.h"


#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <gdt.h>
//#include "gdt.h"

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;



void* _Unwind_Resume = nullptr;
void* __gxx_personality_v0 = nullptr;


//lesson 1
void printf(char* str){

	//lesson3
	//unsigned short* VideoMemory = (unsigned short*)0xb8000;
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	
	/**for(int i = 0; str[i] != '\0'; ++i){
		//覆盖高字节部分
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
	}*/

	//lesson 5
	static uint8_t x = 0,y = 0;

	for(int i = 0; str[i] != '\0'; ++i){

		switch(str[i]){

			case '\n':
				y++;
				x = 0;
				break;

			default:
				VideoMemory[80*y + x] = (VideoMemory[80*y + x] & 0xFF00) | str[i];
				x++;
				break;
		}
		

		if(x >= 80 ){
			y++;
			x = 0;
		}

		if(y >= 25){
			for(y = 0; y < 25; ++y){
				for(x = 0; x < 80; ++x){
					VideoMemory[80*y + x] = (VideoMemory[80*y + x] & 0xFF00) | ' ';
				}
			}
			x = 0;
			y = 0;
		}

	}
}


void printfHex(uint8_t key){
	char* foo = "KEYBOARD 0x00";
	char* hex = "0123456789ABCDEF";
	foo[22] = hex[(key >> 4) & 0x0F];
	foo[23] = hex[key & 0x0F];
	printf(foo);
}


//lesson 02
typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors(){
	for(constructor* i = &start_ctors; i != &end_ctors; ++i){
		(*i)();
	}

}

class PrintKeyboardEventHandler:public KeyboardEventHandler
{
public:
	void OnMouseDown(char c){
		char* foo = " ";
		foo[0] = c;
		printf(foo);
	}
	
};

class MouseToConsole:public MouseEventHandler
{
		int8_t x,y;
public:

	MouseToConsole(){
		
	}

	virtual void OnActivate(){
		uint16_t* VideoMemory = (uint16_t*)0xb8000;
		VideoMemory[80*12 + 40] = ((VideoMemory[80*12 + 40] & 0xF000) >> 4)
		                      | ((VideoMemory[80*12 + 40] & 0x0F00) << 4)
		                      | ((VideoMemory[80*12 + 40]) & 0x00FF);
	}

	virtual void OnMouseMove(int xffset, int yoffset){
		static uint16_t* VideoMemory = (uint16_t*)0xb8000;

			VideoMemory[80*y + x] = ((VideoMemory[80*y + x] & 0xF000) >> 4)
		                      | ((VideoMemory[80*y + x] & 0x0F00) << 4)
		                      | ((VideoMemory[80*y + x]) & 0x00FF);
			x += xffset;
			if(x < 0){
				x = 0;
			}
			if(x >= 80){
				x = 79;
			}



			y += yoffset;
			if(y <= 0){
				y = 0;
			}
			if(y >= 25){
				y = 24;
			}

			VideoMemory[80*y + x] = ((VideoMemory[80*y + x] & 0xF000) >> 4)
		                      | ((VideoMemory[80*y + x] & 0x0F00) << 4)
		                      | ((VideoMemory[80*y + x]) & 0x00FF);
	}
	
};




// linux--printf--glibc  lesson1
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber){

	printf("Hello World!----http://www.Algorithm.de");
	

	//lesson 4
	GlobalDescriptorTable gdt;

	//lesson 06
	//中断实例
	InterruptManager interrupts(0x20, &gdt);
	//InterruptManager interrupts(&gdt);

	printf("Initializing Hardware, Stage 1\n");

	DriverManager drvManager;
	PrintKeyboardEventHandler kbhandler;
	keyboardDriver keyboard(&interrupts, &kbhandler);
	//lesson 09
	drvManager.AddDriver(&keyboard);

	MouseToConsole mousehandler;
	MouseDriver mouse(&interrupts, &mousehandler);

	drvManager.AddDriver(&mouse);


	PeripherComponentInterController PCIController;
	PCIController.SelectDrivers(&drvManager, &interrupts);

	printf("Initializing Hardware, Stage 2\n");
	drvManager.ActivateAll();

	printf("Initializing Hardware, Stage 3\n");
	interrupts.Activate();

	while(1);

}


//lesson 01
//make loader.o
//make kernel.o
//make mykernel.bin
//make install 
//ls boot
//sudo vim /boot/grub/grub.cfg
// add the grub config
//reboot

/**

###BEGIN MYKERNEL ###
  menuentry 'My Operator Syatem' {
	multiboot /boot/mykernel.bin
	boot
  }

###END MYKERNEL###


*/


//lesson 03
//sudo apt-get install VirtualBox grub-legacy xorriso
//make mykernel.iso

//run in Virtualbox