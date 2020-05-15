
#include <hardwarecommunication/pci.h>
using namespace myos::common;
using namespace myos::hardwarecommunication;


void printf(char* str);
void printfHex(uint8_t);


PeripherComponentInterController::PeripherComponentInterController(){

}

PeripherComponentInterController::~PeripherComponentInterController(){

}


PeripherComponentInterController::PeripherComponentInterController()
:dataPort(0xCFC),
commandPort(0xCF8){

}
PeripherComponentInterController::~PeripherComponentInterController(){

}

uint32_t PeripherComponentInterController::Read(uint16_t bus, uint16_t device, uint16_t function, 
		uint32_t registeroffset){
	uint32_t id = 
	 0x1 << 31
	| ((bus & 0xFF) << 16)
	| ((device & 0x1F) << 11)
	| ((function & 0x07) << 8)
	|(registeroffset & 0xFC);

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

bool PeripherComponentInterController::DeviceHasFunctions(common::uint16_t bus, common::uint16_t device){
	return Read(bus, device, 0, 0x0E) & (1 << 7);
}

void PeripherComponentInterController::SelectDrivers(DriverManager* driverManager){
	for(int bus = 0; bus < 8; ++i){
		for(int device = 0 ; device < 32; ++device){
			int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
			for(int functions = 0; functions < numFunctions; ++function){
				PeripherComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);
				
				if(device.vendor_id == 0x0000 || device.vendor_id == 0xFFFF){
					break;
				}

				printf("PCI BUS");
				printfHex(bus & 0xFF);

				printf(" , DEVICE");
				printfHex(device & 0xFF);

				printf(" , FUNCTION");
				printfHex(function & 0xFF);


				printf(" = VENTOR");
				printfHex((dev.vendor_id & 0xFF00) >> 8 );
				printfHex(dev.vendor_id & 0xFF);

				printf(" , DEVICE");
				printfHex((dev.device_id & 0xFF00) >> 8);
				printfHex(dev.device_id & 0xFF);
				printf("\n");
			}
		}
	}
}


//47
PeripherComponentInterconnectDeviceDescriptor PeripherComponentInterController::GetDeviceDescriptor(common::uint16_t bus,
	common::uint16_t device, common::uint16_t function){

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