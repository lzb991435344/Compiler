#ifndef __MYOS_PCI_H
#define __MYOS_PCI_H

#include <hardwarecommunication/port.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
//#include <drivers/amd_am79c973.h>
#include <memorymanagerment.h>

namespace myos{

	namespace hardwarecommunication{


		enum BaseAddressRegisterType{
			MemoryMapping = 0,
			InputOutput = 1
		};


		class BaseAddressRegister
		{
		public:
			BaseAddressRegister();
			~BaseAddressRegister();
			
		//public:
			bool prefetchanble;
			myos::common::uint8_t* address;
			myos::common::uint32_t size;
			BaseAddressRegisterType type;
		};


		class PeripherComponentInterconnectDeviceDescriptor
		{
		public:
			PeripherComponentInterconnectDeviceDescriptor();
			~PeripherComponentInterconnectDeviceDescriptor();

			//structure of pci 
			myos::common::uint32_t portBase;
			myos::common::uint32_t interrupt;

			myos::common::uint16_t bus;
			myos::common::uint16_t device;
			myos::common::uint16_t function;

			myos::common::uint16_t vendor_id;
			myos::common::uint16_t device_id;

			myos::common::uint8_t class_id;
			myos::common::uint8_t subclass_id;
			myos::common::uint8_t interface_id;

			myos::common::uint8_t revision;

			
		};


		class PeripherComponentInterController
		{

			Port32Bit dataPort;
			Port32Bit commandPort;
		public:
			PeripherComponentInterController();
			~PeripherComponentInterController();

			common::uint32_t Read(myos::common::uint16_t bus, myos::common::uint16_t device, myos::common::uint16_t function, 
				myos::common::uint32_t registeroffset);

			myos::common::uint32_t Write(myos::common::uint16_t bus, myos::common::uint16_t device, myos::common::uint16_t function, 
				myos::common::uint32_t registeroffset, myos::common::uint32_t value);

			bool DeviceHasFunctions(common::uint16_t bus, common::uint16_t device);	

			//select drivers
			void SelectDrivers(myos::drivers::DriverManager* driverManager, myos::hardwarecommunication::InterruptManager* interruptManager);

			myos::drivers::Driver* GetDriver(PeripherComponentInterconnectDeviceDescriptor dev,  myos::hardwarecommunication::InterruptManager* interruptManager);
			PeripherComponentInterconnectDeviceDescriptor GetDeviceDescriptor(myos::common::uint16_t bus, myos::common::uint16_t device, myos::common::uint16_t function);
			BaseAddressRegister GetBaseAddressRegister(myos::common::uint16_t bus, myos::common::uint16_t device, myos::common::uint16_t function, myos::common::uint16_t bar);
		};	
	}
}






#endif