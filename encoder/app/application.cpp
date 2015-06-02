#include <user_config.h>
#include <SmingCore/SmingCore.h>

#define encoder0PinA 4 //DT
#define encoder0PinB 5 //CLK
#define BTN 14		   //SW
#define say(a) ( Serial.print(a) )
int encoder0Pos = 0;

void IRAM_ATTR interruptHandler()
{
	if (digitalRead(encoder0PinA) == HIGH) 
	{   
		if (digitalRead(encoder0PinB) == LOW) 
		{  
			encoder0Pos = encoder0Pos - 1;         
		} 
		else
		{
			encoder0Pos = encoder0Pos + 1;        
		}
	}
	else                                        
	{ 
		if (digitalRead(encoder0PinB) == LOW) 
		{   
			encoder0Pos = encoder0Pos + 1;          
		} 
		else 
		{
			encoder0Pos = encoder0Pos - 1;          
		}
	}
  Serial.println (encoder0Pos);          
}

void IRAM_ATTR interruptHandlerButton()
{
	say("Button pushed, reset counter :");
	Serial.println(digitalRead(BTN));
	encoder0Pos = 0;
}

void init()
{
	Serial.begin(SERIAL_BAUD_RATE); // 115200 or 9600 by default
	attachInterrupt(encoder0PinA, interruptHandler, CHANGE);
	attachInterrupt(BTN, interruptHandlerButton, CHANGE);
}
