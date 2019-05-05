// Unstable start of example!!

#include "thread.h"
#include <stdlib.h>

#define NUM_ITEMS 32
#define BUFSIZE 8


thread producer(thread* thread) 
{
  static int produced;
  
  THREAD_START(thread);
  
  for(produced = 0; produced < NUM_ITEMS; ++produced) {
  
    SEMAPHORE_WAIT(thread, &full);
    
    SEMAPHORE_WAIT(thread, &mutex);

    // add to the buffer
    
    SEMAPHORE_SIGNAL(thread, &mutex);
    SEMAPHORE_SIGNAL(thread, &empty);
  }

  THREAD_EXIT(thread);
}

thread consumer(thread* thread)
{
  static int consumed;
  
  THREAD_START(thread);

  for(consumed = 0; consumed < NUM_ITEMS; ++consumed) {
    
    SEMAPHORE_WAIT(thread, &empty);
    
    SEMAPHORE_WAIT(thread, &mutex);    

    // remove from the buffer
    
    SEMAPHORE_SIGNAL(thread, &mutex);
    
    SEMAPHORE_SIGNAL(thread, &full);
  }

  THREAD_EXIT(thread);
}

thread main_thread(thread* thread)
{
  static struct thread producer_thread, consumer_thread;

  THREAD_START(thread);
  
  SEMAPHORE_INIT(&empty, 0);
  SEMAPHORE_INIT(&full, BUFSIZE);
  SEMAPHORE_INIT(&mutex, 1);

  THREAD_INITALIZE(&producer_thread);
  THREAD_INITALIZE(&consumer_thread);

  int ret = THREAD_WAIT_UNTIL(thread, producer(&producer_thread) &
                     consumer(&consumer_thread));

  THREAD_EXIT(thread);
}

void setup(void) {
  Serial.begin(9600);
  static struct semaphore mutex, full, empty;
}

void loop(void) [
  // Initialize buffer
  // Initialize main_thread
}