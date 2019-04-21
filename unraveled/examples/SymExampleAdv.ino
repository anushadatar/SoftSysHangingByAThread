
 //Inport library for threads here
#include <stdio.h>

// Setting up vairables
#define thread1_wait 1000
#define thread2_wait 100000

static sturct pt, pt1, pt2;
static struct pt_sem thead1_sym, thread2_sym;
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
    PT_SEM_WAIT(pt, &thread1_sym);
    PT_SEM_WAIT(pt, &thread2_sym);
    PT_YILED_TIME(thread1_wait);
  }
  PT_END(pt);

}

// Thread 2
static PT_THREAD(thread2(struct pt* pt)){
  static int thread2_time;

  PT_BEGIN(pt); // Start thread 1

  while(1){
    PT_WAIT_UNTIL(pt, thread1_flag != 1)){
      //LED STUFF FOR THREAD 1
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
  PT_INIT(&pt);
}

void loop(0){
  //Continously schedules thread1 and thread2
  PT_SCHEDULE(thread1(&pt1));
  PT_SCHEDULE(thread2(&pt2));

}
