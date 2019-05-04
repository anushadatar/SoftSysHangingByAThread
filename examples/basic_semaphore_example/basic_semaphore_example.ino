// STILL VERY UNSTABLE and doesn't compile

#include <stdio.h>
#include "thread.h"
 
#define NUM_ITEMS 32
#define BUFFER_SIZE 8

// Global variables. Tried to declare them during setup,
// but that did not work, so here we are...
static int buffer[BUFFER_SIZE];
static int buffer_pointer;
static struct semaphore full, empty;

static void add_buffer(int value)
{
  Serial.print("Value ");
  Serial.print(value);
  Serial.print (" added at ");
  Serial.print(buffer_pointer);
  Serial.print("\n");
  buffer[buffer_pointer] = value;
  buffer_pointer = (buffer_pointer + 1) % BUFFER_SIZE;
}
static int get_buffer(void)
{
  int value;
  value = buffer[buffer_pointer];
  Serial.print("Value ");
  Serial.print(value);
  Serial.print (" removed at ");
  Serial.print(buffer_pointer);
  Serial.print("\n");
  buffer_pointer = (buffer_pointer + 1) % BUFFER_SIZE;
  return value;
}

static int create_value(void)
{
  static int value = 0;
  Serial.print("Value ");
  Serial.print(value);
  Serial.print (" created.");
  Serial.print("\n");  
  return value++;
}

static void remove_value(int value)
{
  Serial.print("Value ");
  Serial.print(value);
  Serial.print (" removed.");
  Serial.print("\n");
}
 
static void consumer(struct thread* thread) {
  static int total_consumed;
    
  THREAD_START(thread);
 
  for(total_consumed = 0; total_consumed < NUM_ITEMS; ++total_consumed) {
    SEMAPHORE_WAIT(thread, &empty);
    remove_value(get_buffer());    
    SEMAPHORE_SIGNAL(thread, &full);
  }
  THREAD_CLEAR(thread);
}

static void producer(struct thread *thread) {
  static int total_produced;
  THREAD_START(thread);
  for(total_produced = 0; total_produced < NUM_ITEMS; ++total_produced) {  
    SEMAPHORE_WAIT(thread, &empty); 
    int value = create_value();  
    add_buffer(value);
 
    
    SEMAPHORE_SIGNAL(thread, &full);
  }
  THREAD_CLEAR(thread);
}

 
static thread main_thread(struct thread *thread)
{
  static struct pt pt_producer, pt_consumer;
  THREAD_START(thread);
  SEMAPHORE_INIT(&empty, 0);
  SEMAPHORE_INIT(&full, BUFSIZE);
  THREAD_INITIALIZE(&producer_thread);
  THREAD_INITIALIZE(&consumer_thread);
  THREAD_WAIT_THREAD(thread, producer(&producer_thread) &
         consumer(&consumer_thread));
  THREAD_CLEAR(thread);
}

int main(void)
{
  struct thread main_thread;
  THREAD_INITIALIZE(&main_thread);
  THREAD_SCHEDULE(main_thread(&main_thread))
  return 0;
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.print("Starting...");
}

void loop(void) 
{
  main();
}

