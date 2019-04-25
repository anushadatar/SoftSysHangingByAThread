
//Inport library for threads here
#include <stdio.h>

// Setting up vairables
#define thread1_wait 1000

static sturct pt, pt1;
int thread1_flag = 1;

static PT_THREAD(thread1(struct pt* pt)){
  static int thread1_time;

  PT_BEGIN(pt); // Start thread 1

  while(1){
    thread1_flag = 1;
    delay(1000);
    Serial.println("Still in Thread 1")
    thread1_time = millis() + thread1_wait;
  }
  PT_END(pt);
}

void setup(){
  Serial.begin(9600);
  PT_INIT(&pt);
}

void loop(){
  PT_SCHEDULE(thread1(&pt1));
}
