#ifndef __MYOS__GUI__DESTOP_H
#define __MYOS__GUI__DESTOP_H

#include <gui/widget.h>
#include <drivers/mouse.h>
#include <common/types.h>

namespace myos{
	namespace gui{
		class Destop:public CompositeWidget,public myos::drivers::MouseEventHandler{
		protected:
			myos::common::uint32_t MouseX;
			myos::common::uint32_t MouseY; 

		public:
			Destop(myos::common::int32_t w, myos::common::int32_t h,
				myos::common::uint8_t r, myos::common::uint8_t g, myos::common::uint8_t b);
			~Destop();

			void Draw(myos::common::GraphicsContext* gc);

			void OnMouseDown(myos::common::uint8_t button);
			void OnMouseUp(myos::common::uint8_t button);
			void OnMouseMove(myos::common::int32_t x, myos::common::int32_t y);
		};

	}
}


#endif