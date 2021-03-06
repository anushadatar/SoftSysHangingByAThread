/*
  Threading using the "thread.h" header file and LED displys.

  Creates two threads that each run. Their processes overlap and show the psudo
	thread functionality. The LED bliker object counts milliseconds before updating.
*/


#include "thread.h"
#include <stdio.h>

/*
  Blinkable: OO immplimention of blinking LED's using threads
	ledPin: Sets the output pin
	currState: Used to know when to update the LED state
	beginTime: set when initialized as the start time
	endTime: set when initialized and used to singal the end of ON state
	previousMillis: used to check if update to state is needed

	Update: Checks milliseccnds since last one state and either turns on, off or
	maintains state of LED.

 */

class Blinkable{

  //Set up Value
	int ledPin;

  // State Value
  int currState;

  //Time Values
	long beginTime;
	long endTime;
	unsigned long previousMillis;

  //Init
  public:
    Blinkable(int pinNum, long start, long end){
      ledPin = pinNum;
      pinMode(ledPin, OUTPUT);
      currState = LOW;
      beginTime = start;
      endTime = end;
      previousMillis = 0;
    }

  // Called during each thread to update the LED
  void Update(){
    unsigned long currentMillis = millis();


    if((currState == HIGH) && (currentMillis - previousMillis >= beginTime)){

      // Going to turn off

    	currState = LOW;

      previousMillis = currentMillis;


      digitalWrite(ledPin, LOW);
    }else if ((currState == LOW) && (currentMillis - previousMillis >= endTime)){

      //Going to turn on

      currState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(ledPin, HIGH);
    }
  }
};

// One LED for each thread
Blinkable ledThreadA(6, 50, 300);
Blinkable ledThreadB(7, 250, 550);

static int flag1, flag2;
static struct thread thread1, thread2;

/*
 *  Thread 1's Code
 */
static int example1(struct thread *thread)
{
  THREAD_START(thread);
  while(1) {
    THREAD_WAIT_UNTIL(thread, flag2 != 0);
    ledThreadA.Update();
    /* Flip the flags so the other thread can run. */
    flag2 = 0;
    flag1 = 1;
  }
  THREAD_CLEAR(thread);
}

/*
 *  Thread 2's Code
 */
static int example2(struct thread *thread)
{
  THREAD_START(thread);

  while(1) {
    /* Wait until triggered and then re-flip the flags. */
    flag2 = 1;
    THREAD_WAIT_UNTIL(thread, flag1 != 0);
    ledThreadB.Update();
    flag1 = 0;
  }
  THREAD_CLEAR(thread);
}

/*
 * Setup
 */
void setup(void) {
  Serial.begin(9600);
}

/*
 * Loop
 */
void loop(void)
{
  /* Initialize threads */
  THREAD_INITIALIZE(&thread1);
  THREAD_INITIALIZE(&thread2);
  /* Run the two threads forever. */
  while(1) {
    example1(&thread1);
    example2(&thread2);
  }
}
