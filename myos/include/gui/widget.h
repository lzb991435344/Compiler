#ifndef __MYOS_WIDGET_H
#define __MYOS_WIDGET_H

#include <common/types.h>
#include <common/graphicscontext.h>

namespace myos{
	namespace gui{

		class Widget
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



		public:
			Widget(Widget* parent, myos::common::uint8_t x, myos::common::uint8_t y, 
				myos::common::uint8_t w, myos::common::uint8_t h, myos::common::uint8_t r,
				myos::common::uint8_t g, myos::common::uint8_t b);
			~Widget();
			
			virtual void GetFocus(Widget* widget);
			virtual void ModelToScreen(myos::common::uint32_t &x, myos::common::uint32_t &y);

			virtual void Draw(GraphicsContex* gc);
			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t x, myos::common::uint32_t y);

			virtual void OnKeyUp(myos::common::uint32_t x, myos::common::uint32_t y);
			virtual void OnKeyDown(myos::common::uint32_t x, myos::common::uint32_t y);
		};

	}
}




#endif