

#include <drivers/vga.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;


VideoGraphicsArray::VideoGraphicsArray()
:miscPort(0x3c2),
crtcIndexPort(0x3d4),
crtcDataPort(0x3d5),
sequenceIndexPort(0x3c4),
sequenceDataPort(0x3c5),
graphicsControllerIndexPort(0x3ce),
graphicsControllerDataPort(0x3cf),
attributeControllerIndexPort(0x3c0),
attributeControllerReadPort(0x3c1),
attributeControllerWritePort(0x3c0),
attributeControllerResetPort(0x3d0){

}
VideoGraphicsArray::~VideoGraphicsArray(){

}

bool VideoGraphicsArray::SetMode(int64_t width,  int64_t height, uint32_t colordepth){
	
	//not support
	if(!SupportsMode(width, height, colordepth)){
		return false;
	}

	unsigned char g_320x200x256[] ={
		/*MISC*/
		0x63,
		/*SEQ*/
		0x03, 0x01, 0x0F, 0x00, 0x0E,
		/**CRTC*/
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
		0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
		0xFF,

		/*GC*/
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
		0xFF,
		/**AC*/
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x41, 0x00, 0x0F, 0x00, 0x00
	};

	WriteRegisters(g_320x200x256);
	return true;
	

}
bool VideoGraphicsArray::SupportsMode(int64_t width, int64_t height, uint32_t colordepth){
	return width == 320 && height == 200 && colordepth == 8; 
}

void VideoGraphicsArray::PutPixel(uint32_t x, uint32_t y, uint8_t colorIndex){
	uint8_t* pixelAddress = GetFrameBufferSegment() + 320*y + x;	
	*pixelAddress = colorIndex;

}


void VideoGraphicsArray::PutPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b){
	PutPixel(x, y , GetColorIndex(r, g, b));
}
uint8_t VideoGraphicsArray::GetColorIndex(uint8_t r, uint8_t g, uint8_t b){
	if((r == 0x00 && g == 0x00 && b == 0x00)){
		return 0x00;//black
	}
	if((r == 0x00 && g == 0x00 && b == 0xA8)){
		return 0x01;//blue
	}
	if((r == 0x00 && g == 0xA8 && b == 0x00)){
		return 0x02;//green
	}
	if((r == 0xA8 && g == 0x00 && b == 0x00)){
		return 0x04;//red
	}
	if((r == 0xFF && g == 0xFF && b == 0xA8)){
		return 0x3F;//white
	}
	return 0x00;
}

//使用颜色填充屏幕区域
void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b){
		for(uint32_t Y = y; Y < y + h; ++Y){
			for(uint32_t X = x; X < x + w; ++X){
				PutPixel(X, Y, r, g, b);
			}
		}
}

void VideoGraphicsArray::WriteRegisters(myos::common::uint8_t* registers){
	//misc
	miscPort.Write(*(registers++));

	//sequence
	for(uint8_t i = 0; i < 5; ++i){
		sequenceIndexPort.Write(i);
		sequenceDataPort.Write(*(registers)++);

	}

	//set data and lock
	crtcIndexPort.Write(0x03);
	crtcDataPort.Write(crtcDataPort.Read() | 0x80);

	crtcIndexPort.Write(0x11);
	crtcDataPort.Write(crtcDataPort.Read() & ~0x80);


	registers[0x03] = registers[0x03] | 0x80;
	registers[0x11] = registers[0x11] & ~0x80;

	//catchode ray tude controller
	for(uint8_t i = 0; i < 25; ++i){
		crtcIndexPort.Write(i);
		crtcDataPort.Write(*(registers++));

	}

	// graphics  controller
	for(uint8_t i = 0; i < 9; ++i){
		graphicsControllerIndexPort.Write(i);
		graphicsControllerDataPort.Write(*(registers++));

	}

	//attribute controller
	for(uint8_t i = 0; i < 21; ++i){
		attributeControllerResetPort.Read();
		attributeControllerIndexPort.Write(i);
		attributeControllerWritePort.Write(*(registers++));

	}

	//reset attribute, reset indexport
	attributeControllerResetPort.Read();
	attributeControllerIndexPort.Write(0x20);

}
uint8_t* VideoGraphicsArray::GetFrameBufferSegment(){
	graphicsControllerIndexPort.Write(0x06);
	uint8_t segmentNumber = ((graphicsControllerDataPort.Read()) & 0x03);

	switch(segmentNumber){
		default:
			case 0: return (uint8_t*)0x00000;
			case 1: return (uint8_t*)0xA0000; 
			case 2: return (uint8_t*)0xB0000;
			case 3:	return (uint8_t*)0xB8000;
			break;
	}


}
