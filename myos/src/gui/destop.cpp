
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

void Destop::Draw(myos::common::GraphicsContex* gc){

}

void Destop::OnMouseDown(uint8_t button){
	CompositeWidget::OnMouseDown(MouseX, MouseY, button);
}
void Destop::OnMouseUp(uint8_t button){
	CompositeWidget::OnMouseUp(MouseX, MouseY, button);
}
void Destop::OnMouseMove(int32_t x, int32_t y){
	int32_t newMouseX = MouseX + x;
	if(newMouseX){

	}
}