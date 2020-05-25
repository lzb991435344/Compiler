#ifndef __MYOS__ATA_H
#define __MYOS__ATA_H

#include <common/types.h>
#include <hardwarecommunication/port.h>


namespace myos{
	namespace drivers{

		class AdvancedTechnologyAttachment
		{
		protected:
			myos::hardwarecommunication::Port16Bit dataPort;
			myos::hardwarecommunication::Port8Bit errorPort;
			myos::hardwarecommunication::Port8Bit sectorCountPort;
			myos::hardwarecommunication::Port8Bit lbaLowPort;
			myos::hardwarecommunication::Port8Bit lbaMidPort;
			myos::hardwarecommunication::Port8Bit lbaHiPort;
			myos::hardwarecommunication::Port8Bit devicePort;
			myos::hardwarecommunication::Port8Bit commandPort;
			myos::hardwarecommunication::Port8Bit controlPort;

			bool master;//master or slave
			myos::common::uint16_t bytePerSector;
		public:
			AdvancedTechnologyAttachment(myos::common::uint16_t portBase, bool master);
			~AdvancedTechnologyAttachment();

			void Identify();
			void Read28(myos::common::uint32_t sector, myos::common::uint8_t* data, int count);
			void Write28(myos::common::uint32_t sector, myos::common::uint8_t* data, int count);

			void Flush();
			
		};
	}
}






#endif