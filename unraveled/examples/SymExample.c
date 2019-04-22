
 //Inport library for threads here
#include <stdio.h>
#include "thread.h"

// Setting up vairables
#define thread1_wait 1000
#define thread2_wait 100000

int thread1_flag = 1;
int thread2_flag = 0;


void doTheThread2Thing(){
  printf("%s\n", "Thread 2");
   // Blinks on and off slowly
}

void doTheThread1Thing(){
  printf("%s\n", "Thread 1");
   // Blinks on and off quickly
}

long getSec(){
  return 1000;
}

// Thread 1
static PT_THREAD(doTheThread1Thing(struct pt* pt)){
  static int thread1_time;

  THREAD_BEGIN(pt); // Start thread 1

  while(1){
    THREAD_WAIT_UNTIL(pt, thread2_flag != 1)){
      //LED STUFF FOR THREAD 1
    }
    thread2_flag = 0;
    thread1_flag = 1;
    THREAD_YIELD(pt, getSec() > thread1_time);
    thread1_time = getSec() + thread1_wait;
  }
  THREAD_END(pt);

}


// Thread 2
static PT_THREAD(doTheThread2Thing(struct pt* pt)){
  static int thread2_time;

  THREAD_BEGIN(pt); // Start thread 1

  while(1){
    THREAD_WAIT_UNTIL(pt, thread1_flag != 1)){
      //LED STUFF FOR THREAD 2
    }
    thread1_flag = 0;
    thread2_flag = 1;
    THREAD_YIELD(pt, getSec() > thread2_time);
    thread2_time = getSec() + thread2_wait;
  }
  THREAD_END(pt);

}

// Main

static struct pt;
static struct pt2;
static struct pt1;


int main(int argc, char **argv){


  // PT_INIT(&pt);
  THREAD_INIT(&pt1);
  THREAD_INIT(&pt2);

  while(1){
    PT_SCHEDULE(doTheThread1Thing(&pt1));
    PT_SCHEDULE(doTheThread2Thing(&pt2));
  }

  return 0;
}
