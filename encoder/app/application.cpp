#include <user_config.h>
#include <SmingCore/SmingCore.h>

#define encoder0PinA 4   
#define encoder0PinB 5
#define BTN 14
#define say(a) ( Serial.print(a) )
int encoder0Pos = 0;

void IRAM_ATTR interruptHandler()
{
	if (digitalRead(encoder0PinA) == HIGH) 
	{   // found a low-to-high on channel A
		if (digitalRead(encoder0PinB) == LOW) 
		{  // check channel B to see which way
			encoder0Pos = encoder0Pos - 1;         // CCW
		} 
		else
		{
			encoder0Pos = encoder0Pos + 1;         // CW
		}
	}
  else                                        // found a high-to-low on channel A
  { 
    if (digitalRead(encoder0PinB) == LOW) {   // check channel B to see which way
                                              // encoder is turning  
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }

  }
  Serial.println (encoder0Pos);          // debug - remember to comment out
                                              // before final program run
  // you don't want serial slowing down your program if not needed
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

	delay(3000);
	say("======= Bring GPIO");
	//say( DT);
	say( " low to trigger interrupt(s) =======");
	Serial.println();

	attachInterrupt(encoder0PinA, interruptHandler, CHANGE);
	attachInterrupt(BTN, interruptHandlerButton, CHANGE);
	
}
