#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"

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

//lesson 02
typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors(){
	for(constructor* i = &start_ctors; i != &end_ctors; ++i){
		(*i)();
	}

}



// linux--printf--glibc  lesson1
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber){

	printf("Hello World!----http://www.Algorithm.de");
	printf("Hello World!----http://www.Algorithm.de");

	//lesson 4
	GlobalDescriptorTable gdt;

	//lesson 06
	//中断实例
	InterruptManager interrupts(&gdt);

	keyboardDriver keyboard(&interrupts);
	MouseDriver mouse(&interrupts);

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