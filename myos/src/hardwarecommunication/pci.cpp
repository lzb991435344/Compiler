
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/amd_am79c973.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;
using namespace myos::drivers;


void printf(char* str);
void printfHex(uint8_t);


BaseAddressRegister::BaseAddressRegister(){

}
BaseAddressRegister::~BaseAddressRegister(){
	
}


PeripherComponentInterconnectDeviceDescriptor::PeripherComponentInterconnectDeviceDescriptor(){

}

PeripherComponentInterconnectDeviceDescriptor::~PeripherComponentInterconnectDeviceDescriptor(){

}


PeripherComponentInterController::PeripherComponentInterController()
:dataPort(0xCFC),
commandPort(0xCF8){

}
PeripherComponentInterController::~PeripherComponentInterController(){

}

uint32_t PeripherComponentInterController::Read(uint16_t bus, uint16_t device, uint16_t function, 
		uint32_t registeroffset){
	uint32_t id = (0x1 << 31) | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11)| ((function & 0x07) << 8)|(registeroffset & 0xFC);

	commandPort.Write(id);
	uint32_t result = dataPort.Read();
	return result >> (8*(registeroffset % 4));
}

uint32_t PeripherComponentInterController::Write(uint16_t bus, uint16_t device, uint16_t function, 
		uint32_t registeroffset, uint32_t value){
	uint32_t id = 
	 0x1 << 31
	| ((bus & 0xFF) << 16)
	| ((device & 0x1F) << 11)
	| ((function & 0x07) << 8)
	| (registeroffset & 0xFC);

	commandPort.Write(id);
	dataPort.Write(value);
}

bool PeripherComponentInterController::DeviceHasFunctions(myos::common::uint16_t bus, myos::common::uint16_t device){
	return Read(bus, device, 0, 0x0E) & (1 << 7);
}

void PeripherComponentInterController::SelectDrivers(myos::drivers::DriverManager* driverManager, myos::hardwarecommunication::InterruptManager* interruptManager){
	for(int bus = 0; bus < 8; ++bus){
		for(int device = 0 ; device < 32; ++device){
			int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
			for(int function = 0; function < numFunctions; ++function){
				PeripherComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);
				
				if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF){
					//break;

					// cat pci message
					//lspci -n 
					//lspi -x
					continue;
				}

				//baseaddressregister
				for(int barNum = 0; barNum < 6; ++barNum){
					BaseAddressRegister bar = GetBaseAddressRegister(bus, device, function, barNum);
					
					if(bar.address &&(bar.type == InputOutput)){
						dev.portBase = (uint32_t)bar.address;
					}					
				}

				//it only need a driver
				myos::drivers::Driver* driver = GetDriver(dev, interruptManager);
					if(driver != 0){
						 driverManager->AddDriver(driver);
					}

				printf("PCI BUS");
				printfHex(bus & 0xFF);
				printf("\n");

				printf(" , DEVICE");
				printfHex(device & 0xFF);
				printf("\n");

				printf(" , FUNCTION");
				printfHex(function & 0xFF);
				printf("\n");


				printf(" = VENTOR");
				printfHex((dev.vendor_id & 0xFF00) >> 8 );
				printfHex(dev.vendor_id & 0xFF);
				printf("\n");

				printf(" , DEVICE");
				printfHex((dev.device_id & 0xFF00) >> 8);
				printfHex(dev.device_id & 0xFF);
				printf("\n");
			}
		}
	}
}



myos::drivers::Driver* PeripherComponentInterController::GetDriver(PeripherComponentInterconnectDeviceDescriptor dev, 
 myos::hardwarecommunication::InterruptManager* interruptManager){
	
	myos::drivers::Driver* driver = 0;
	switch(dev.vendor_id){
		case 0x1022://AMD
			switch(dev.device_id){
				case 0x2000://am79c973
					//driver = new (amd_am79c973*)MemoryManage::activeMemoryManager->malloc(sizeof(amd_am79c973));
					driver = (Driver*)MemoryManage::activeMemoryManager->malloc(sizeof(amd_am79c973));
					if(driver != 0){
						new (driver)amd_am79c973(&dev, interruptManager);
					}
					return driver;
					printf("AMD am79c973\n");
					break;
			}
		break;

		case 8086://Intel

		break;

	}

	switch(dev.class_id){
		case 0x03://graphics
			switch(dev.subclass_id){
				case 0x00://VGA
				break;
			}
		break;
	}

	return driver;
}


BaseAddressRegister PeripherComponentInterController::GetBaseAddressRegister(uint16_t bus, myos::common::uint16_t device, uint16_t function, uint16_t bar){
	BaseAddressRegister result;

	uint32_t headertype = Read(bus, device, function, 0x0E) & 0x7F;
	int MaxBARS = 6 - (4 * headertype);

	if(bar > MaxBARS){
		return result;
	}

	/**
		00:03.0 Ethernet controller: Red Hat, Inc. Virtio network device
		00: f4 1a 00 10 07 04 10 00 00 00 00 02 00 00 00 00
		10: 61 c0 00 00 00 10 bf fe 00 00 00 00 00 00 00 00
		20: 00 00 00 00 00 00 00 00 00 00 00 00 f4 1a 01 00
		30: 00 00 be fe 40 00 00 00 00 00 00 00 0b 01 00 00

	*/
	uint32_t bar_value = Read(bus, device, function, 0x10 + 4*bar);
	result.type = (bar_value & 0x01) ?InputOutput:MemoryMapping;

	uint32_t temp;
	if(result.type = MemoryMapping){
		switch((bar_value >> 1) & 0x3){
			//32 Bit Mode
			case 0:

			//20 Bit Mode  
			case 1:

			//64 Bit Mode
			case 2:
			break;

		}
	}else{//IntputOutput

		result.address = (uint8_t*)(bar_value & ~0x3);
		result.prefetchanble = false;
	}

	return result;
}

//47
PeripherComponentInterconnectDeviceDescriptor PeripherComponentInterController::GetDeviceDescriptor(myos::common::uint16_t bus,
	myos::common::uint16_t device, myos::common::uint16_t function){

	PeripherComponentInterconnectDeviceDescriptor result;

	result.bus = bus;
	result.device = device;
	result.function = function;

	result.vendor_id = Read(bus, device, function, 0x00);
	result.device_id = Read(bus, device, function, 0x02);

	result.class_id = Read(bus, device, function, 0x0b); ;
	result.subclass_id = Read(bus, device, function, 0x0a);
	result.interface_id = Read(bus, device, function, 0x09);

	result.revision = Read(bus, device, function, 0x08);
	result.interrupt = Read(bus, device, function, 0x3c);

	return result;

}