#ifndef __MYOS_WIDGET_H
#define __MYOS_WIDGET_H

#include <common/types.h>
#include <common/graphicscontext.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
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
			

			//virtual bool AddChild(Widget* widget);
			virtual void GetFocus(Widget* widget);
			virtual void ModelToScreen(myos::common::int32_t &x, myos::common::int32_t &y);

			virtual void Draw(common::GraphicsContext* gc);
			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t x, myos::common::uint32_t y);

			virtual bool ContaisCoordinate(myos::common::uint32_t x, myos::common::uint32_t y);

			//virtual void OnKeyUp(myos::common::uint32_t x, myos::common::uint32_t y);
			//virtual void OnKeyDown(myos::common::uint32_t x, myos::common::uint32_t y);
		};

		class CompositeWidget:public Widget,public myos::drivers::MouseEventHandler
		{
		public:
			CompositeWidget(Widget* parent, myos::common::uint8_t x, myos::common::uint8_t y, 
				myos::common::uint8_t w, myos::common::uint8_t h, myos::common::uint8_t r,
				myos::common::uint8_t g, myos::common::uint8_t b);
			~CompositeWidget();
			virtual void GetFocus(Widget* widget);
			virtual void ModelToScreen(myos::common::uint32_t &x, myos::common::uint32_t &y);

			virtual void Draw(common::GraphicsContext* gc);
			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t newx, myos::common::uint32_t newy);

			virtual bool AddChild(Widget* widget);
			virtual void OnKeyUp(char str);
			virtual void OnKeyDown(char  str);	
		
		private:
			Widget* children[100];
			int numChildren;
			Widget* focussedChild;
		};

	}
}


#endif