#include <gui/widget.h>


Widget::Widget(Widget* parent, uint8_t x, uint8_t y, 
				uint8_t w, uint8_t h, uint8_t r,
				uint8_t g, uint8_t b){
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;
}

Widget::~Widget(){

}
			
 void Widget::GetFocus(Widget* widget){
 	if(parent != 0){
 		parent->GetFocus(widget);
 	}
 }


void Widget::ModelToScreen(uint32_t &x, uint32_t &y){
	if(parent != 0){
		parent->ModelToScreen(x, y);
	}
	x += this->x;
	y += this->y;
}


void Widget::Draw(GraphicsContex* gc){

}


void Widget::OnMouseDown(uint32_t x, uint32_t y){

}


void Widget::OnMouseUp(uint32_t x, uint32_t y){

}


void Widget::OnMouseMove(uint32_t oldx, uint32_t oldy, uint32_t x, uint32_t y){

}



void Widget::OnKeyUp(uint32_t x, uint32_t y){

}


void Widget::OnKeyDown(uint32_t x, uint32_t y){

}