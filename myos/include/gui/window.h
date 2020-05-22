#ifndef __MYOS__GUI__WINDOW__H
#define __MYOS__GUI__WINDOW__H

#include <gui/widget.h>
#include <drivers/mouse.h>
#include <common/types.h>

namespace myos{
	namespace gui{
		class Window:public CompositeWidget
		{
		protected:
			bool Dragging;
		public:
			Window(Widget* parent, myos::common::uint8_t x, myos::common::uint8_t y, 
				myos::common::uint8_t w, myos::common::uint8_t h, myos::common::uint8_t r,
				myos::common::uint8_t g, myos::common::uint8_t b);
			~Window();

			virtual void OnMouseDown(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseUp(myos::common::uint32_t x, myos::common::uint32_t y, myos::common::uint8_t button);
			virtual void OnMouseMove(myos::common::uint32_t oldx, myos::common::uint32_t oldy, myos::common::uint32_t newx, myos::common::uint32_t newy);
	
		};
	}
}






#endif