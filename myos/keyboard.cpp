#include "keyboard.h"
#include "types.h"
#include "interrupts.h"
#include "gdt.h"
#include "mouse.h"

void printf(char* str);
void printfHex(uint8_t);


KeyboardEventHandler::KeyboardEventHandler(){

}


void KeyboardEventHandler::OnKeyDown(char){

}
void KeyboardEventHandler::OnKeyUp(char ){

}


//lesson 09
keyboardDriver::keyboardDriver(InterruptManager* manage, KeyboardEventHandler* handler)
//:InterruptHandler(manage, 0x21),
:InterruptHandler(0x21, manage),
dataport(0x60),
commandport(0x64)
{
	this->handler = handler;
}
keyboardDriver::~keyboardDriver(){

}

void keyboardDriver::Activate(){
	while(commandport.Read() & 0x1){
 		dataport.Read();
 	}
 	commandport.Write(0xae); //activate interrupt
 	commandport.Write(0x20); //get current stay

 	uint8_t status = (dataport.Read() | 1) & ~0x10;
 	commandport.Write(0x60); //set state
 	dataport.Write(status);

 	dataport.Write(0xf4);
}


uint32_t keyboardDriver::HandleInterrupt(uint32_t esp){
	uint8_t key = dataport.Read();
	/**char* foo = 'KEYBOARD 0x00';
	char* hex = '0123456789ABCDEF';
	foo[22] = hex[(key >> 4) & 0x0F];
	foo[23] = hex[key & 0x0F];
	printf(foo);*/

	/*
	if(key < 0x80){
		switch(key){
			case 0xFA:
			break;

			case 0x1E:
			printf('a');
			break;

			case 0x45:
			case 0xC5:
			break;

			default:
			char* foo = 'KEYBOARD 0x00';
			char* hex = '0123456789ABCDEF';
			foo[22] = hex[(key >> 4) & 0x0F];
			foo[23] = hex[key & 0x0F];
			printf(foo)
			break;
		}
	}*/
	
	if(handler == 0){
		return esp;
	}
	//lesson08 mouse
	static bool Shift = false;

	switch(key){

		case 0x02: if(Shift) handler->OnKeyDown('!'); else handler->OnKeyDown('1'); break;
		case 0x03: if(Shift) handler->OnKeyDown('\''); else handler->OnKeyDown('2'); break;
		case 0x04: if(Shift) handler->OnKeyDown('**'); else handler->OnKeyDown('3'); break;
		case 0x05: if(Shift) handler->OnKeyDown('$'); else handler->OnKeyDown('5'); break;
		case 0x06: if(Shift) handler->OnKeyDown('%'); else handler->OnKeyDown('6'); break;
		case 0x07: if(Shift) handler->OnKeyDown('&'); else handler->OnKeyDown('7'); break;
		case 0x08: if(Shift) handler->OnKeyDown('/'); else handler->OnKeyDown('4'); break;
		case 0x09: if(Shift) handler->OnKeyDown('('); else handler->OnKeyDown('8'); break;
		case 0x0A: if(Shift) handler->OnKeyDown(')'); else handler->OnKeyDown('9'); break;
		case 0x0B: if(Shift) handler->OnKeyDown('='); else handler->OnKeyDown('0'); break;


		case 0x10: if(Shift) handler->OnKeyDown('Q'); else handler->OnKeyDown('q'); break;
		case 0x11: if(Shift) handler->OnKeyDown('W'); else handler->OnKeyDown('w'); break;
		case 0x12: if(Shift) handler->OnKeyDown('E'); else handler->OnKeyDown('e'); break;
		case 0x13: if(Shift) handler->OnKeyDown('R'); else handler->OnKeyDown('r'); break;
		case 0x14: if(Shift) handler->OnKeyDown('T'); else handler->OnKeyDown('t'); break;
		case 0x15: if(Shift) handler->OnKeyDown('Z'); else handler->OnKeyDown('z'); break;
		case 0x16: if(Shift) handler->OnKeyDown('U'); else handler->OnKeyDown('u'); break;
		case 0x17: if(Shift) handler->OnKeyDown('I'); else handler->OnKeyDown('i'); break;
		case 0x18: if(Shift) handler->OnKeyDown('O'); else handler->OnKeyDown('o'); break;
		case 0x19: if(Shift) handler->OnKeyDown('P'); else handler->OnKeyDown('p'); break;

		case 0x1E: if(Shift) handler->OnKeyDown('A'); else handler->OnKeyDown('a'); break;
		case 0x1F: if(Shift) handler->OnKeyDown('S'); else handler->OnKeyDown('s'); break;
		case 0x20: if(Shift) handler->OnKeyDown('D'); else handler->OnKeyDown('d'); break;
		case 0x21: if(Shift) handler->OnKeyDown('F'); else handler->OnKeyDown('f'); break;
		case 0x22: if(Shift) handler->OnKeyDown('G'); else handler->OnKeyDown('g'); break;
		case 0x23: if(Shift) handler->OnKeyDown('H'); else handler->OnKeyDown('h'); break;
		case 0x24: if(Shift) handler->OnKeyDown('J'); else handler->OnKeyDown('j'); break;
		case 0x25: if(Shift) handler->OnKeyDown('K'); else handler->OnKeyDown('k'); break;
		case 0x26: if(Shift) handler->OnKeyDown('L'); else handler->OnKeyDown('l'); break;


		case 0x2C: if(Shift) handler->OnKeyDown('Y'); else handler->OnKeyDown('y'); break;
		case 0x2D: if(Shift) handler->OnKeyDown('X'); else handler->OnKeyDown('x'); break;
		case 0x2E: if(Shift) handler->OnKeyDown('C'); else handler->OnKeyDown('c'); break;
		case 0x2F: if(Shift) handler->OnKeyDown('V'); else handler->OnKeyDown('v'); break;
		case 0x30: if(Shift) handler->OnKeyDown('B'); else handler->OnKeyDown('b'); break;
		case 0x31: if(Shift) handler->OnKeyDown('N'); else handler->OnKeyDown('n'); break;
		case 0x32: if(Shift) handler->OnKeyDown('M'); else handler->OnKeyDown('m'); break;
		case 0x33: if(Shift) handler->OnKeyDown(';'); else handler->OnKeyDown(','); break;
		case 0x34: if(Shift) handler->OnKeyDown(':'); else handler->OnKeyDown('.'); break;
		case 0x35: if(Shift) handler->OnKeyDown('_'); else handler->OnKeyDown('-'); break;

  		case 0x1C: handler->OnKeyDown('\n'); break;
  		case 0x39: handler->OnKeyDown(' '); break;
  		case 0x2A: case 0x36: Shift = true; break;
  		case 0xAA: case 0xB6: Shift = false; break;

  		case 0x45: break;
		default:
		//test key
		if(key < 0x80){
			printf("KEYBOARD 0x00");
			printfHex(key);
			/*char* hex = '0123456789ABCDEF';
			foo[22] = hex[(key >> 4) & 0x0F];
			foo[23] = hex[key & 0x0F];
			printf(foo);*/
		}
		break;
	}

	return esp;
}