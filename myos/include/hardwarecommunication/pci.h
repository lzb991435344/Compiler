#include __MYOS_PCI_H
#define __MYOS_PCI_H

#include <hardwarecommunication/port.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>


namespace myos{

	namespace hardwarecommunication{
		class PeripherComponentInterconnectDeviceDescriptor
		{
		public:
			PeripherComponentInterconnectDeviceDescriptor();
			~PeripherComponentInterconnectDeviceDescriptor();

			//structure of pci 
			common::uint32_t portBase;
			common::uint32_t interrupt;

			common::uint16_t bus;
			common::uint16_t device;
			common::uint16_t funtion;

			common::uint16_t vendor_id;
			common::uint16_t device_id;

			common::uint8_t class_id;
			common::uint8_t subclass_id;
			common::uint8_t interface_id;

			common::uint8_t revision;

			
		};


		class PeripherComponentInterController
		{

			Port32Bit dataPort;
			Port32Bit commandPort;
		public:
			PeripherComponentInterController();
			~PeripherComponentInterController();

			common::uint32_t Read(common::uint16_t bus, common::uint16_t device, common::uint16_t function, 
				common::uint32_t registeroffset);

			common::uint32_t Write(common::uint16_t bus, common::uint16_t device, common::uint16_t function, 
				common::uint32_t registeroffset, common::uint32_t value);

			bool DeviceHasFunctions(common::uint16_t bus, common::uint16_t device);	

			//select drivers
			void SelectDrivers(myos::DriverManager* driverManager);

			PeripherComponentInterconnectDeviceDescriptor GetDeviceDescriptor(common::uint16_t bus, common::uint16_t device, common::uint16_t function);
		};	
	}
}






#endif