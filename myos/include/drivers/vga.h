#ifndef __MYOS__VGA_H
#define __MYOS__VGA_H

#include <hardwarecommunication/port.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>



namespace myos{
	namespace drivers{
    

    class VideoGraphicsArray
    {
    public:
    	VideoGraphicsArray();
    	//virtual ~VideoGraphicsArray();
    	~VideoGraphicsArray();

    	virtual bool SetMode(myos::common::int64_t width, myos::common::int64_t height, myos::common::uint32_t colordepth);
    	virtual bool SupportsMode(myos::common::int64_t width, myos::common::int64_t height, myos::common::uint32_t colordepth);

    	virtual void PutPixel(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t colorIndex);
    	virtual void PutPixel(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t r, myos::common::uint8_t g, myos::common::uint8_t b);
    	virtual myos::common::uint8_t GetColorIndex(myos::common::uint8_t r, myos::common::uint8_t g, myos::common::uint8_t b);


    protected:
    	/**
    	myos::hardwarecommunication:Port8Bit miscPort;
    	myos::hardwarecommunication:Port8Bit crtcIndexPort;
    	myos::hardwarecommunication:Port8Bit crtcDataPort;
    	myos::hardwarecommunication:Port8Bit sequenceIndexPort;
    	myos::hardwarecommunication:Port8Bit sequenceDataPort;
    	myos::hardwarecommunication:Port8Bit graphicsControllerIndexPort;
    	myos::hardwarecommunication:Port8Bit graphicsControllerDataPort;
    	myos::hardwarecommunication:Port8Bit attributeControllerIndexPort;
    	myos::hardwarecommunication:Port8Bit attributeControllerReadPort;
    	myos::hardwarecommunication:Port8Bit attributeControllerWritePort;
    	myos::hardwarecommunication:Port8Bit attributeControllerResetPort;*/
    	
    	hardwarecommunication::Port8Bit miscPort;
    	hardwarecommunication::Port8Bit crtcIndexPort;
    	hardwarecommunication::Port8Bit crtcDataPort;
    	hardwarecommunication::Port8Bit sequenceIndexPort;
    	hardwarecommunication::Port8Bit sequenceDataPort;
    	hardwarecommunication::Port8Bit graphicsControllerIndexPort;
    	hardwarecommunication::Port8Bit graphicsControllerDataPort;
    	hardwarecommunication::Port8Bit attributeControllerIndexPort;
    	hardwarecommunication::Port8Bit attributeControllerReadPort;
    	hardwarecommunication::Port8Bit attributeControllerWritePort;
    	hardwarecommunication::Port8Bit attributeControllerResetPort;
   		void WriteRegisters(myos::common::uint8_t* registers);
   		myos::common::uint8_t* GetFrameBufferSegment();
    };


	}
}


#endif