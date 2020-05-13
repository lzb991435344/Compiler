#ifndef __MOUSE_H
#define __MOUSE_H

#include "port.h"
#include "types.h"
#include "interrupts.h"
#include "driver.h"

class MouseEventHandler{
public:
	MouseEventHandler();

	virtual void Activate();
	virtual void OnMouseDown(uint8_t button);
	virtual void OnMouseUp(uint8_t button);
	virtual void OnMouseMove(int x, int y);
};


class MouseDriver:public InterruptHandler,public Driver
{
	Port8Bit dataport;
	Port8Bit commandport;

	uint8_t buffer[3];
	uint8_t offset;
	uint8_t buttons;

   MouseEventHandler* handler;

public:
	MouseDriver(InterruptManager* manage, MouseEventHandler* handler);
	~MouseDriver();
	virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Activate();
};





#endif