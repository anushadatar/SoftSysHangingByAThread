#include <stdio.h> 
#include "thread.h"

// Flag variable for each thread.
static int thread1_flag, thread2_flag;
static struct thread thread1, thread2;


static int thread1(thread *thread)
{
  THREAD_BEGIN(thread);

  while(1) {
  
    PT_WAIT_UNTIL(thread, thread2_flag != 0);
    printf("Thread 1 is running\n");

    thread2_flag = 0;
    thread1_flag = 1;
  }
  THREAD_END(thread);
}

static int thread2(struct thread *thread)
{
  THREAD_BEGIN(thread);
  while(1) {
    thread2_flag = 1;
    PT_WAIT_UNTIL(thread, thread1_flag != 0);
    printf("Thread 2 is running\n");
    thread1_flag = 0;

  }
  THREAD_END(thread);
}

int main(void) 
{
  THREAD_INIT(&thread1);
  THREAD_INIT(&thread2);
  
  while(1) {
    thread1(&thread1);
    thread2(&thread2);
  }
}

