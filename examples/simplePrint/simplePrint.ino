
/*
 *  Creates and runs two threads. A simple print statement is printed from each thread.
 */


#include "thread.h"
#include <stdio.h>

static int flag1, flag2;
static struct thread thread1, thread2;

/*
 *  Thread 1's code
 */
static int example1(struct thread *thread)
{
  THREAD_START(thread);
  while(1) {
    THREAD_WAIT_UNTIL(thread, flag2 != 0);
    Serial.println("Protothread 1 running\n");
    /* Flip the flags so the other thread can run. */
    flag2 = 0;
    flag1 = 1;
  }
  THREAD_CLEAR(thread);
}

/*
 *  Thread 2's code
 */
static int example2(struct thread *thread)
{
  THREAD_START(thread);

  while(1) {
    /* Wait until triggered and then re-flip the flags. */
    flag2 = 1;
    THREAD_WAIT_UNTIL(thread, flag1 != 0);
    Serial.println("Protothread 2 running\n");
    flag1 = 0;
  }
  THREAD_CLEAR(thread);
}

/*
 * Setup
 */
void setup(void) {
  Serial.begin(9600);
  Serial.println("Running serial...");
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
