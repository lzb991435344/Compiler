#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "port.h"
#include "types.h"
#include "interrupts.h"


class keyboardDriver:public InterruptHandler
{
	Port8Bit dataport;
	Port8Bit commandport;

public:
	keyboardDriver(InterruptManager* manage);
	~keyboardDriver();
	virtual uint32_t HandleInterrupt(uint32_t esp);
};



#endif