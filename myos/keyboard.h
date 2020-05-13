#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "port.h"
#include "types.h"
#include "interrupts.h"
#include "driver.h"

//lesson 09
class KeyboardEventHandler{
public:
	KeyboardEventHandler();


	virtual void OnKeyDown(char);
	virtual void OnKeyUp(char);
};


class keyboardDriver:public InterruptHandler,public Driver
{
	Port8Bit dataport;
	Port8Bit commandport;

	KeyboardEventHandler* handler;
public:
	keyboardDriver(InterruptManager* manage, KeyboardEventHandler* handler);
	~keyboardDriver();
	virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Activate();
};



#endif