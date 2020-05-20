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

	this->Focusable = true;
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
	int X = 0;
	int Y = 0;
	ModelToScreen(X, Y);
	gc->FileRectangle(X, Y, w, h, r, g, b);
}


void Widget::OnMouseDown(uint32_t x, uint32_t y){
	if(Focusable){
		GetFocus(this);
	}
}


void Widget::OnMouseUp(uint32_t x, uint32_t y){

}


void Widget::OnMouseMove(uint32_t oldx, uint32_t oldy, uint32_t x, uint32_t y){

}


/**
void Widget::OnKeyUp(uint32_t x, uint32_t y){

}


void Widget::OnKeyDown(uint32_t x, uint32_t y){

}*/


void Widget::ContaisCoordinate(uint32_t x, uint32_t y){
	return this->x <= x && x < this->x + this->w
		  && this->y <= y && y < this->y + this->h;

}

//

CompositeWidget::CompositeWidget(Widget* parent, uint8_t x, uint8_t y, 
				uint8_t w, uint8_t h, uint8_t r,uint8_t g, uint8_t b)
:Widget(parent, x, y, w, h, r, g, b){
	focussedChild = 0;
	numChildren = 0;


}
CompositeWidget::~CompositeWidget(){

}


 void CompositeWidget::AddChild(Widget* child){
 	if(numChildren >= 100){
 		return false;
 	}
 	children[numChildren++] = child;
 	return true;

 }
void CompositeWidget::GetFocus(Widget* widget){
	this->focussedChild = widget;
	if(parent != 0){
		parent->GetFocus(this);
	}
}
void CompositeWidget::ModelToScreen(uint32_t &x, uint32_t &y){

}

void CompositeWidget::Draw(GraphicsContex* gc){
	Widget::Draw();
	for(int i = numChildren - 1; i > 0 ; ++i){
		children[i]->Draw(gc);
	}
}

void CompositeWidget::OnMouseDown(uint32_t x, uint32_t y, uint32_t button){
	for(int i = 0; i < numChildren; ++i){
		if(children[i]->ContaisCoordinate(x - this->x, y - this->y)){
			children[i]->OnMouseDown(x - this->x, y - this->y);
			break;
		}
	}
}
void CompositeWidget::OnMouseUp(uint32_t x, uint32_t y, uint32_t button){
	for(int i = 0; i < numChildren; ++i){
		if(children[i]->ContaisCoordinate(x - this->x, y - this->y)){
			children[i]->OnMouseUp(x - this->x, y - this->y);
			break;
		}
	}
}
void CompositeWidget::OnMouseMove(uint32_t oldx, uint32_t oldy, uint32_t newx, uint32_t newy){
	int firstchild = -1;
	for(int i = 0; i < numChildren; ++i){
		if(children[i]->ContaisCoordinate(oldx - this->x, oldy - this->y)){
			children[i]->OnMouseUp(x - this->x, y - this->y, newx - this->x, newy - this->y);
			firstchild = i;
			break;
		}
	}

	for(int i = 0; i < numChildren; ++i){
		if(children[i]->ContaisCoordinate(newx - this->x, newy - this->y)){
			if(firstchild != i){
				children[i]->OnMouseDown(oldx - this->x, oldy - this->y, newx - this->x, newy - this->y);
			}
			break;
		}
	}	
}

void CompositeWidget::OnKeyUp(uint32_t x, uint32_t y){
	if(focussedChild != 0){
		focussedChild->OnMouseUp(x - this->x, y - this->y);
	}
}
void CompositeWidget::OnKeyDown(uint32_t x, uint32_t y){
	if(focussedChild != 0){
		focussedChild->OnKeyDown(x - this->x, y - this->y);
	}
}	