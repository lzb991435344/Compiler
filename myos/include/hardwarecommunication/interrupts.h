#ifndef __MYOS__INTERRUPTS_H
#define __MYOS__INTERRUPTS_H

//lesson 06
#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>

//lesson07

namespace myos{
	namespace hardwarecommunication{

		class InterruptManager;

		class InterruptHandler
		{
		protected:
			myos::common::uint8_t interruptNumber;
			InterruptManager* interruptManager;

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


			static void InterruptIgnore();

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

			static void HandleInterruptException0x00();
			static void HandleInterruptException0x01();
			static void HandleInterruptException0x02();
			static void HandleInterruptException0x03();
			static void HandleInterruptException0x04();
			static void HandleInterruptException0x05();
			static void HandleInterruptException0x06();
			static void HandleInterruptException0x07();
			static void HandleInterruptException0x08();
			static void HandleInterruptException0x09();
			static void HandleInterruptException0x0A();
			static void HandleInterruptException0x0B();
			static void HandleInterruptException0x0C();
			static void HandleInterruptException0x0D();
			static void HandleInterruptException0x0E();
			static void HandleInterruptException0x0F();
			static void HandleInterruptException0x10();
			static void HandleInterruptException0x11();
			static void HandleInterruptException0x12();
			static void HandleInterruptException0x13();

			static myos::common::uint32_t handlerInterrupt(myos::common::uint8_t interruptNumber, myos::common::uint32_t esp);
			
			//lesson07
			myos::common::uint32_t DoHandlerInterrupt(myos::common::uint8_t interruptNumber, myos::common::uint32_t esp);

			Port8BitSlow programInterruptControllerMasterCommand;
			Port8BitSlow programInterruptControllerMasterData;
			Port8BitSlow programInterruptControllerSlaveCommand;
			Port8BitSlow programInterruptControllerSlaveData;
		public:
			InterruptManager(myos::common::uint16_t hardwareInterruptOffset,  myos::GlobalDescriptorTable* globalDescriptorTable);
			~InterruptManager();
			myos::common::uint16_t HardwareInterruptOffset();

			void Activate();
			//lesson07
			void Deactivate();
			

			static void IgnoreInterruptRequest();
		};
	}
}



#endif 