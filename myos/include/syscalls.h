#ifndef __MYOS__SYACALLS_H
#define __MYOS__SYACALLS_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/multitasking.h>

namespace myos{
	class SyscallHandler:public hardwarecommunication::InterruptHandler
	{
	public:
		SyscallHandler(myos::hardwarecommunication::InterruptManager* interruptManager, 
			myos::common::uint8_t InterruptNumber);
		~SyscallHandler();
		

		virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
	};
}




#endif