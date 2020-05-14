#ifndef __MYOS__DRIVERS__KEYBOARD_H
#define __MYOS__DRIVERS__KEYBOARD_H

#include <hardwarecommunication/port.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>

//

namespace myos {
	namespace drivers{
		//lesson 09
		class KeyboardEventHandler{
		public:
			KeyboardEventHandler();


			virtual void OnKeyDown(char);
			virtual void OnKeyUp(char);
		};


		class keyboardDriver:public myos::hardwarecommunication::InterruptHandler,public Driver
		{
			myos::hardwarecommunication::Port8Bit dataport;
			myos::hardwarecommunication::Port8Bit commandport;

			KeyboardEventHandler* handler;
		public:
			keyboardDriver(myos::hardwarecommunication::InterruptManager* manage, KeyboardEventHandler* handler);
			~keyboardDriver();
			virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
			virtual void Activate();
		};
	}
}




#endif