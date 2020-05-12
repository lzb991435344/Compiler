#include <types.h>

//lesson 1
void printf(char* str){

	//lesson3
	//unsigned short* VideoMemory = (unsigned short*)0xb8000;
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	
	for(int i = 0; str[i] != '\0'; ++i){
		//覆盖高字节部分
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
	}
}

//lesson 02
typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" callConstructors(){
	for(constructor* i = &start_ctors; i != end_ctors; ++i){
		(*i)();
	}

}



// linux--printf--glibc  lesson1
extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber){

	printf("Hello World!----http://www.Algorithm.de");

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