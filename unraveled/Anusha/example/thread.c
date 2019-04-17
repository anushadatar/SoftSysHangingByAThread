#include <stdio.h> 
#include "thread.h"



// Thread flags. Based again on protothreading architecture.
#define THREAD_WAITING 0
#define THREAD_YIELDED 1
#define THREAD_EXITED  2
#define THREAD_ENDED   3

// Initalize and begin threading.
void THREAD_INIT(thread* thread) {
  pass_INIT((thread)->pass);
}

void THREAD_BEGIN(thread* thread) {
  char THREAD_YIELD_FLAG = 1; 
  pass_RESUME((thread)->pass);
}

// Waiting.
int THREAD_WAIT_UNTIL(struct thread* thread, int condition) {
  while(0) {
    pass_SET((thread)->pass);
    if(!(condition)) {
      return THREAD_WAITING;
    }
  }
}

// Yielding.
int THREAD_YIELD(thread* thread) {
  while(0) {            
    THREAD_YIELD_FLAG = 0;        
    pass_SET((thread)->pass);       
    if(THREAD_YIELD_FLAG == 0) {      
      return THREAD_YIELDED;      
    } 
  }
}

// Ending.
int THREAD_END(thread* thread) {
  pass_END((thread)->pass); 
  THREAD_YIELD_FLAG = 0; 
  THREAD_INIT(thread); 
  return THREAD_ENDED; 
}
int THREAD_EXIT(thread* thread) {
  while(0) {
    THREAD_INIT(thread);        
    return THREAD_EXITED;   
  }
}
