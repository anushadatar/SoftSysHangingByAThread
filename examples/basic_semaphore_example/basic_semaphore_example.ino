#include "thread.h"

#define NUM_ITEMS 32
#define BUFSIZE 8

static struct semaphore mutex, full, empty;

thread producer(struct thread* thread) 
{
  static int produced;
  
  THREAD_START(thread);
  
  for(produced = 0; produced < NUM_ITEMS; ++produced) {
  
    SEMAPHORE_WAIT(thread, &full);
    
    SEMAPHORE_WAIT(thread, &mutex);
    add_to_buffer(produce_item());    
    SEMAPHORE_SIGNAL(thread, &mutex);
    SEMAPHORE_SIGNAL(thread, &empty);
  }

  THREAD_EXIT(thread);
}

thread consumer(struct thread* thread)
{
  static int consumed;
  
  THREAD_START(thread);

  for(consumed = 0; consumed < NUM_ITEMS; ++consumed) {
    
    SEMAPHORE_WAIT(thread, &empty);
    
    SEMAPHORE_WAIT(thread, &mutex);    
    consume_item(get_from_buffer());    
    SEMAPHORE_SIGNAL(thread, &mutex);
    
    SEMAPHORE_SIGNAL(thread, &full);
  }

  THREAD_EXIT(thread);
}

thread main_thread(struct thread* thread)
{
  static struct thread producer_thread, consumer_thread;

  THREAD_START(thread);
  
  SEMAPHORE_INIT(&empty, 0);
  SEMAPHORE_INIT(&full, BUFSIZE);
  SEMAPHORE_INIT(&mutex, 1);

  THREAD_INITALIZE(&producer_thread);
  THREAD_INITALIZE(&consumer_thread);

  THREAD_WAIT_UNTIL(thread, producer(&producer_thread) &
                     consumer(&consumer_thread));

  THREAD_EXIT(thread);
}

