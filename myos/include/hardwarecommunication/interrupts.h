#ifndef __MYOS__INTERRUPTS_H
#define __MYOS__INTERRUPTS_H

//lesson 06
#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>
#include <multitasking.h>
//lesson07

namespace myos{
	namespace hardwarecommunication{

		class InterruptManager;

		class InterruptHandler
		{
		protected:
			myos::common::uint8_t interruptNumber;
			InterruptManager* interruptManager;
			TaskManager* taskManager;

			InterruptHandler(myos::common::uint8_t interruptNumber, InterruptManager* interruptManager);
		    ~InterruptHandler();

		public:
			myos::common::uint32_t handlerInterrupt(myos::common::uint32_t esp);
		};


		class InterruptManager
		{
		friend class InterruptHandler;
		protected:

			//lesson07
			static InterruptManager* ActiveInterruptManager;
			InterruptHandler* handlers[256];
			TaskManager* taskManager;
			
			struct GateDescriptor{
				myos::common::uint16_t  handlerAddressLowBits;
				myos::common::uint16_t gdt_codeSegmentSelector;
				myos::common::uint8_t reserved;
				myos::common::uint8_t access;
				myos::common::uint16_t handlerAddressHighBits;
			}__attribute__((packed));


			static GateDescriptor interruptDescriptorTable[256];

			struct InterruptDescriptorTablePointer{
				myos::common::uint16_t size;
				myos::common::uint32_t base;
			}__attribute__((packed));



			static void setInterruptDescriptorTableEntry(
				myos::common::uint8_t interruptNumber,
				myos::common::uint16_t gdt_codeSegmentSelectorOffset,
				void (*handler) (),
				myos::common::uint8_t DescriptorPrivilegeLevel,
				myos::common::uint8_t DescriptorType
			);


			
			
			static void HandleInterruptRequest0x00();
			static void HandleInterruptRequest0x01();
			static void HandleInterruptRequest0x02();
			static void HandleInterruptRequest0x03();
			static void HandleInterruptRequest0x04();
			static void HandleInterruptRequest0x05();
			static void HandleInterruptRequest0x06();
			static void HandleInterruptRequest0x07();
			static void HandleInterruptRequest0x08();
			static void HandleInterruptRequest0x09();
			static void HandleInterruptRequest0x0A();
			static void HandleInterruptRequest0x0B();
			static void HandleInterruptRequest0x0C();
			static void HandleInterruptRequest0x0D();
			static void HandleInterruptRequest0x0E();
			static void HandleInterruptRequest0x0F();
			static void HandleInterruptRequest0x31();

			static void HandleException0x00();
			static void HandleException0x01();
			static void HandleException0x02();
			static void HandleException0x03();
			static void HandleException0x04();
			static void HandleException0x05();
			static void HandleException0x06();
			static void HandleException0x07();
			static void HandleException0x08();
			static void HandleException0x09();
			static void HandleException0x0A();
			static void HandleException0x0B();
			static void HandleException0x0C();
			static void HandleException0x0D();
			static void HandleException0x0E();
			static void HandleException0x0F();
			static void HandleException0x10();
			static void HandleException0x11();
			static void HandleException0x12();
			static void HandleException0x13();

			static myos::common::uint32_t HandleInterrupt(myos::common::uint8_t interruptNumber, myos::common::uint32_t esp);
			
			//lesson07
			myos::common::uint32_t DoHandlerInterrupt(myos::common::uint8_t interruptNumber, myos::common::uint32_t esp);

			Port8BitSlow programInterruptControllerMasterCommand;
			Port8BitSlow programInterruptControllerMasterData;
			Port8BitSlow programInterruptControllerSlaveCommand;
			Port8BitSlow programInterruptControllerSlaveData;
		public:
			InterruptManager(myos::common::uint16_t hardwareInterruptOffset,  myos::GlobalDescriptorTable* globalDescriptorTable,
				myos::TaskManager* taskManager);
			~InterruptManager();
			myos::common::uint16_t HardwareInterruptOffset;

			void Activate();
			//lesson07
			void Deactivate();
			
			static void InterruptIgnore();
			static void IgnoreInterruptRequest();
		};
	}
}



#endif 