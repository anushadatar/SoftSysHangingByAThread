/*
  Threading using the "thread.h" header file and LCD Display.

  Creates two threads that each run. Their processes overlap and show the psudo
	thread functionality. A message from each thread is sent to the LCD screen.
*/

#include "thread.h"
#include <stdio.h>
#include <LiquidCrystal.h> // LCD Screen


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char* ThreadAMessage;
char* ThreadBMessage;

static int flag1, flag2;
static struct thread thread1, thread2;


/*
  Displayer: OO immplimention of displaying on LCD screen
	currState: Used to know when if it is being used
	beginTime: set when initialized as the start time
	endTime: set when initialized and used to singal the end of ON state
	previousMillis: used to check if update to state is needed
	message: the message to be displayed with an ON state

	Update: Checks if needed to be cleared and displayed the new message

 */



class Displayer{

	long beginTime;
	long endTime;
	long durationTime;
	unsigned long previousMillis;
	int currState;
	char * message;

  //Init
  public:
    Displayer(long start, long end, long duration, char* Tmessage){

			beginTime = start;
			endTime = end;
			durationTime = duration;
			previousMillis = 0;
      Serial.println("LCD is set up\n");
			currState = 0;
			message = Tmessage;

    }

  // Called during each thread to update the LED
  void Update(){
		unsigned long currentMillis = millis();
		if((currState == 1) && (currentMillis - previousMillis >= durationTime)){

      // Going to turn off

    	currState = 0;

      previousMillis = currentMillis;

			lcd.clear();
      lcd.noDisplay();
    }else if ((currState == 0) && (currentMillis - previousMillis <= durationTime)){

      //Going to turn on
      currState = 1;
      previousMillis = currentMillis;
			lcd.display();
			lcd.print(message);
    }

	}

};


// Messages for each thead
char* MessageA = "This is Thread A";
char* MessageB = "Hi from Thread B";


// Declaring Seperate instance of each thread LCD display
Displayer LCDThreadA(50, 300, 500, MessageA);
Displayer LCDThreadB(250, 550, 500, MessageB);


/*
 *  Thread 1's Code
 */
static int example1(struct thread *thread){
  THREAD_START(thread);
  while(1) {
    THREAD_WAIT_UNTIL(thread, flag2 != 0);
    LCDThreadA.Update();
    /* Flip the flags so the other thread can run. */
    flag2 = 0;
    flag1 = 1;
  }
  THREAD_CLEAR(thread);
}

/*
 *  Thread 2's Code
 */
static int example2(struct thread *thread){
  THREAD_START(thread);

  while(1) {
    /* Wait until triggered and then re-flip the flags. */
    flag2 = 1;
    THREAD_WAIT_UNTIL(thread, flag1 != 0);
    LCDThreadB.Update();
    flag1 = 0;
  }
  THREAD_CLEAR(thread);
}

/*
 * Setup
 */
void setup(void) {
  Serial.begin(9600);
	lcd.begin(16, 2);
}

/*
 * Loop
 */
void loop(void){
  /* Initialize threads */
  THREAD_INITALIZE(&thread1);
  THREAD_INITALIZE(&thread2);
  /* Run the two threads forever. */
  while(1) {
    example1(&thread1);
    example2(&thread2);
  }
}
