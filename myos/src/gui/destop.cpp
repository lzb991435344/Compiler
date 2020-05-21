
#include <gui/destop.h>

using namespace myos;
using namespace myos::common;
using namespace myos::gui;




Destop::Destop(int32_t w, int32_t h, uint8_t r, uint8_t g, uint8_t b)
:CompositeWidget(0, 0, 0, w, h, r, g, b), MouseEventHandler(){
	MouseX = w/2;
	MouseY = h/2;
}
Destop::~Destop(){

}

void Destop::Draw(myos::common::GraphicsContext* gc){
	CompositeWidget::Draw(gc);

	for(int i = 0; i < 4; ++i){
		gc->PutPixel(MouseX - i, MouseY, 0xFF, 0xFF, 0xFF);
		gc->PutPixel(MouseX + i, MouseY, 0xFF, 0xFF, 0xFF);
		gc->PutPixel(MouseX, MouseY - i, 0xFF, 0xFF, 0xFF);
		gc->PutPixel(MouseX, MouseY + i, 0xFF, 0xFF, 0xFF);
	}
}

void Destop::OnMouseDown(uint8_t button){
	CompositeWidget::OnMouseDown(MouseX, MouseY, button);
}
void Destop::OnMouseUp(uint8_t button){
	CompositeWidget::OnMouseUp(MouseX, MouseY, button);
}
void Destop::OnMouseMove(int32_t x, int32_t y){
	x /= 4;
	y /= 4;

	int32_t newMouseX = MouseX + x;
	if(newMouseX < 0){
		newMouseX = 0;
	}
	if(newMouseX > w){
		newMouseX = w - 1;
	}

	int32_t newMouseY = MouseY + y;
	if(newMouseY < 0){
		newMouseY = 0;
	}
	if(newMouseY > h){
		newMouseY = h - 1;
	}


	CompositeWidget::OnMouseMove(MouseX, MouseY, newMouseX, newMouseY);
}