#include <gui/window.h>


using namespace myos;
using namespace myos::common;
using namespace myos::gui;


Window::Window(Widget* parent, uint8_t x, uint8_t y, 
				uint8_t w, uint8_t h, uint8_t r,
				uint8_t g, uint8_t b)
:CompositeWidget(parent, x, y, w, h, r, g, b){
	Dragging = false;
}
Window::~Window(){

}

void Window::OnMouseDown(uint32_t x, uint32_t y, uint8_t button){

	Dragging = button ==1;
	CompositeWidget::OnMouseDown(x, y , button);
}
void Window::OnMouseUp(uint32_t x, uint32_t y, uint8_t button){
	Dragging = false;
	CompositeWidget::OnMouseUp(x, y , button);
}
void Window::OnMouseMove(uint32_t oldx, uint32_t oldy, uint32_t newx, uint32_t newy){
	if(Dragging){
		this->x += newx - oldx;
		this->y += newy - oldy;
	}
	CompositeWidget::OnMouseMove(oldx, oldy, newx, newy);
}