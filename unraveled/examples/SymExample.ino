
 //Inport library for threads here
#include <stdio.h>

// Setting up vairables
#define thread1_wait 1000
#define thread2_wait 100000

static sturct pt, pt1, pt2;
int thread1_flag = 1;
int thread2_flag = 0;

void doTheThread2Thing(){
// Blinks Led 2 on and off fast for 1 second
  //At 30 seconds, unblocks thread 1
}

void doTheThread1Thing(){
  // Blinks Led 1 on and off slowly for 1 second
     //At 30 seconds, unblocks thread 2
}

// Thread 1
static PT_THREAD(thread1(struct pt* pt)){
  static int thread1_time;

  PT_BEGIN(pt); // Start thread 1

  while(1){
    PT_WAIT_UNTIL(pt, thread2_flag != 1)){
      //LED STUFF FOR THREAD 1
    }
    thread2_flag = 0;
    thread1_flag = 1;
    PT_YIELD_UNTIL(pt, millis() > thread1_time);
    thread1_time = millis() + thread1_wait;
  }
  PT_END(pt);

}


// Thread 2
static PT_THREAD(thread2(struct pt* pt)){
  static int thread2_time;

  PT_BEGIN(pt); // Start thread 1

  while(1){
    PT_WAIT_UNTIL(pt, thread1_flag != 1)){
      //LED STUFF FOR THREAD 2
    }
    thread1_flag = 0;
    thread2_flag = 1;
    PT_YIELD_UNTIL(pt, millis() > thread2_time);
    thread2_time = millis() + thread2_wait;
  }
  PT_END(pt);

}

// Main

void setup(){
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7,OUTPUT);
}

void loop(0){
  PT_INIT(&pt);
  while(1){
    PT_SCHEDULE(thread1(&pt1));
    PT_SCHEDULE(thread2(&pt2));
  }
}
