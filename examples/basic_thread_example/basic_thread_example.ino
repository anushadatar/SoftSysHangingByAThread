/* 
  Basic example of threading using the "thread.h" header file.
  
  Should create two threads that each run when the other is not 
  running by switching the values of two flags. 
*/

#include "thread.h"
#include <stdio.h> 

// Flags to trigger each thread.
static int flag1, flag2;
// Structs for each thread.
static struct thread thread1, thread2;

/* 
  example1 : First thread to execute.

  thread : Pointer to thread object to kick off.
 */
static int example1(struct thread *thread)
{
  THREAD_START(thread);
  while(1) {
    THREAD_WAIT_UNTIL(thread, flag2 != 0);
    Serial.println("Thread 1 running\n");
    /* Flip the flags so the other thread can run. */
    flag2 = 0;
    flag1 = 1;
  }
  THREAD_CLEAR(thread);
}

/* 
  example2 : Second thread to execute.

  thread : Pointer to thread object to kick off.
 */
static int example2(struct thread *thread)
{
  THREAD_START(thread);

  while(1) {
    /* Wait until triggered and then re-flip the flags. */
    flag2 = 1;
    THREAD_WAIT_UNTIL(thread, flag1 != 0);
    Serial.println("Thread 2 running\n");
    flag1 = 0;
  }
  THREAD_CLEAR(thread);
}

/*
  setup : Literally just kicks off and runs Serial so we can see the threads running. 
*/
void setup(void) {
  Serial.begin(9600);
  Serial.println("Running serial...");
}

/*
  loop : Initializes the two threads and then runs them forever. 
*/
void loop(void)
{  
  /* Initialize threads */
  THREAD_INITALIZE(&thread1);
  THREAD_INITALIZE(&thread2);
  /* Run the two threads forever. */
  while(1) {
    example1(&thread1);
    example2(&thread2);
  }
}

