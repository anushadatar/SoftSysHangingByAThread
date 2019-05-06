/*
  Basic semaphore example using thread.h displayed with LCD screen.

  Creates a bounded buffer that a producer thread adds to
  until it reaches capacity and then a consumer thread removes from until it is
  empty. Displays thread semaphores
*/

#include <stdio.h>
#include "thread.h"

#include <LiquidCrystal.h> // LCD Screen

// Keep constants as preprocessor definitions.
#define TOTAL_NUM_ITEMS 32
#define BUFFER_SIZE 8

// Shared variables between all of the threads involved.
static int buffer[BUFFER_SIZE];
static int buffer_pointer;
static struct semaphore full, empty;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

struct thread main_thread_object;



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
  void update(){
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



class Displayer{

	long beginTime;
	long endTime;
	long durationTime;
	unsigned long previousMillis;
	int currState;
	char * message;

  //Init
  public:
    Displayer(long start, long duration){

			beginTime = start;
			durationTime = duration;
			previousMillis = 0;
      Serial.println("LCD is set up\n");
			currState = 0;

    }

  // Called during each thread to update the LED
  void update(int value){
		unsigned long currentMillis = millis();
		if((currState == 1) && (currentMillis - previousMillis >= durationTime)){

      // Going to turn off

    	currState = 0;

      previousMillis = currentMillis;
//
			lcd.clear();
      lcd.noDisplay();
    }else if ((currState == 0) && (currentMillis - previousMillis <= durationTime)){

      //Going to turn on
      currState = 1;
      previousMillis = currentMillis;
			lcd.display();
			lcd.print(value);
      Serial.println(value);
    }

	}

};

Displayer MainDisplayer(0, 150);

Blinkable ledThreadA(6, 150, 300);
Blinkable ledThreadB(7, 0, 0);

/*
Consumer thread that removes from bounded buffer and then
signals when empty.

thread : Pointer to thread to make the consumer.
*/
static int consumer(struct thread* thread) {
  static int total_consumed;
  THREAD_START(thread);
  // Go through the total number of values to remove from the buffer.
  for(total_consumed = 0; total_consumed < TOTAL_NUM_ITEMS; ++total_consumed) {
    // Wait until the buffer is full.
    SEMAPHORE_WAIT(thread, &full);
    // Print the value.
    int value;
    lcd.display();
    ledThreadA.update();
    value = (int) buffer[buffer_pointer];
		MainDisplayer.update(value);
    // Move buffer pointer, signal accordingly.
    buffer_pointer = (buffer_pointer + 1) % BUFFER_SIZE;
    SEMAPHORE_SIGNAL(thread, &empty);
  }
  THREAD_CLEAR(thread);
}

/*
Producer thread that adds to bounded buffer and then
signals when full.

thread : Pointer to thread to make the producer.
*/
static int producer(struct thread *thread) {
  static int total_produced;
  THREAD_START(thread);
  // Go through the total number of values to add to the buffer.
  for(total_produced = 0; total_produced < TOTAL_NUM_ITEMS; ++total_produced) {
    // Wait until the buffer is empty.
    SEMAPHORE_WAIT(thread, &empty);
    int value = total_produced;
		MainDisplayer.update(value);
    ledThreadB.update();
    buffer[buffer_pointer] = value;
    // Move buffer pointer, signal accordingly.
    buffer_pointer = (buffer_pointer + 1) % BUFFER_SIZE;
    SEMAPHORE_SIGNAL(thread, &full);
  }
  THREAD_CLEAR(thread);
}




/*
Main thread that initializes the producer and the consumer
and the associated semaphores.

thread : Pointer to thread to make the main thread.
*/
static int main_thread(struct thread *thread){

  static struct thread producer_thread, consumer_thread;
  THREAD_START(thread);
  SEMAPHORE_INIT(&empty, 0);
  SEMAPHORE_INIT(&full, BUFFER_SIZE);
  THREAD_INITIALIZE(&producer_thread);
  THREAD_INITIALIZE(&consumer_thread);
  THREAD_WAIT_THREAD(thread, producer(&producer_thread) &
         consumer(&consumer_thread));
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
	THREAD_INITIALIZE(&main_thread_object);
	while(THREAD_SCHEDULE(main_thread(&main_thread_object))) {
		delay(1000);
	}
}
