/*
  Basic semaphore example using thread.h.
  
  Creates a bounded buffer that a producer thread adds to
  until it reaches capacity and then a consumer thread removes from until it is 
  empty. 
*/

#include <stdio.h>
#include "thread.h"

// Keep constants as preprocessor definitions.
#define TOTAL_NUM_ITEMS 32
#define BUFFER_SIZE 8

// Shared variables between all of the threads involved.
static int buffer[BUFFER_SIZE];
static int buffer_pointer;
static struct semaphore full, empty;

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
    value = (int) buffer[buffer_pointer];
    Serial.print("Value ");
    Serial.print(value);
    Serial.print (" removed at ");
    Serial.print(buffer_pointer);
    Serial.print("\n");
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
    Serial.print("Value ");
    Serial.print(value);
    Serial.print (" added at ");
    Serial.print(buffer_pointer);
    Serial.print("\n");
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
static int main_thread(struct thread *thread)
{
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
Kick off serial.
*/
void setup(void) 
{
  Serial.begin(9600);
  Serial.print("Starting...");
}

/*
Main loop for the main thread. Schedules thread and creates a delay
to allow both threads to run at once without interference and still
print to some output.
*/
void loop(void)
{
    struct thread main_thread_object;
    THREAD_INITIALIZE(&main_thread_object);
    while(THREAD_SCHEDULE(main_thread(&main_thread_object))) {
      delay(10);
    }
}

