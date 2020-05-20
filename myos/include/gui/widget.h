#ifndef __MYOS_WIDGET_H
#define __MYOS_WIDGET_H

#include <common/types.h>
#include <common/graphicscontext.h>
#include <drivers/keyboard.h>
namespace myos{
	namespace gui{

		class Widget:public myos::drivers::KeyboardEventHandler
		{

		protected:
			Widget* parent;
			myos::common::uint8_t x;
			myos::common::uint8_t y;
			myos::common::uint8_t w;
			myos::common::uint8_t h;
			myos::common::uint8_t r;
			myos::common::uint8_t g;
			myos::common::uint8_t b;

			bool Focusable;

		public:
			Widget(Widget* parent, myos::common::uint8_t x, myos::common::uint8_t y, 
				myos::common::uint8_t w, myos::common::uint8_t h, myos::common::uint8_t r,
				myos::common::uint8_t g, myos::common::uint8_t b);
			~Widget();
			
			virtual void GetFocus(Widget* widget);
			virtual bool AddChild(Widget* widget);
			virtual void ModelToScreen(myos::common::uint32_t &x, myos::common::uint32_t &y);

			virtual void Draw(myos::common::GraphicsContex* gc);
			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t x, myos::common::uint32_t y);

			virtual bool ContaisCoordinate(myos::common::uint32_t x, myos::common::uint32_t y);

			//virtual void OnKeyUp(myos::common::uint32_t x, myos::common::uint32_t y);
			//virtual void OnKeyDown(myos::common::uint32_t x, myos::common::uint32_t y);
		};

		class CompositeWidget:public Widget,public MouseEventHandler
		{
		public:
			CompositeWidget(Widget* parent, myos::common::uint8_t x, myos::common::uint8_t y, 
				myos::common::uint8_t w, myos::common::uint8_t h, myos::common::uint8_t r,
				myos::common::uint8_t g, myos::common::uint8_t b);
			~CompositeWidget();
			virtual void GetFocus(Widget* widget);
			virtual void ModelToScreen(myos::common::uint32_t &x, myos::common::uint32_t &y);

			virtual void Draw(GraphicsContex* gc);
			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint32_t button);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint32_t button);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t newx, myos::common::uint32_t newy);

			virtual void OnKeyUp(char);
			virtual void OnKeyDown(char);	
		
		private:
			Widget* child[100];
			int numChildren;
			Widget* focussedChild;
		};


	}
}




#endif