#include <stdio.h>
#include "thread.h"
// #include "thread-switch.h"

// Thread flags. Based again on protothreading architecture.
#define THREAD_WAITING 0
#define THREAD_YIELDED 1
#define THREAD_EXITED  2
#define THREAD_ENDED   3

int i = 0;

// Based heavily on protothreading example.

// void PASS_INIT(int s){
//   s = 0;
// }
//
// void PASS_SET(int s){
//   s = __LINE__;
// }
//
// void PASS_END(int s){
//   //NOT sure what goes here
//   // s= 0;
// }

// void PASS_RESUME(int s){
//   switch(s) {
//   case 0:
//     PASS_SET(s);
//   case __LINE__:
//     PASS_END(s);
//   }
// }

// Waiting.
int THREAD_WAIT_UNTIL(struct thread* thread, int condition) {
  printf("%s\n", "at wait");
  do {
    PASS_SET((thread)->pass);
    if(!(condition)) {
      return THREAD_WAITING;
    }
  } while(0);

}


void THREAD_INIT(thread* thread) {
  PASS_INIT((thread)->pass);
}

void THREAD_BEGIN(struct thread* thread) {
  char THREAD_YIELD_FLAG = 1;
  PASS_RESUME((thread)->pass);
}
// Yielding.
int THREAD_YIELD(struct thread* thread) {
  while(0) {
    PASS_SET((thread)->pass);
    return THREAD_YIELDED;
    }
  }

// Ending.
int THREAD_END(struct thread* thread) {
  PASS_END((thread)->pass);
  THREAD_INIT(thread);
  return THREAD_ENDED;
}

int THREAD_EXIT(struct thread* thread) {
  while(0) {
    THREAD_INIT(thread);
    return THREAD_EXITED;
  }
}
