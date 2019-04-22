#include <stdio.h>
#include "thread.h"


// // Flag variable for each thread.
static int thread1_flag, thread2_flag;
static struct thread thread1, thread2;

static int thread1_function(struct thread* t)
{
  THREAD_BEGIN(t);

  while(1) {

    THREAD_WAIT_UNTIL(t, thread2_flag != 0);
    printf("Thread 1 is running\n");

    thread2_flag = 1;
    thread1_flag = 0;
  }
  printf("%s\n", "At 1");
  THREAD_END(t);
}
//
static int thread2_function(struct thread* t )
{
  THREAD_BEGIN(t);
  printf("%s\n","at two" );
  while(1) {
    thread2_flag = 0;
    THREAD_WAIT_UNTIL(t, thread1_flag != 0);
    printf("Thread 2 is running\n");
    thread1_flag = 1;
  }
  THREAD_END(t);
}

int main(void)
{
  printf("%s\n", "At beginning");
  THREAD_INIT(&thread1);
  THREAD_INIT(&thread2);
  printf("%s\n", "At end");
  while(1) {

    thread1_function(&thread1);
    thread2_function(&thread2);
  }
}
