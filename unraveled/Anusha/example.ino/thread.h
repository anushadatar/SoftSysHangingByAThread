#ifndef _THREAD_H_
#define __THREAD_H_

// Switch statement based implementation of local continuation
// based protothreading architecture.
typedef unsigned short pass_t;
#define pass_INIT(s) s = 0;
#define pass_RESUME(s) switch(s) { case 0:
#define pass_SET(s) s = __LINE__; case __LINE__:
#define pass_END(s) }

// A thread just contains one of these objects.
struct thread {
  pass_t pass;
};

// Thread flags. Based again on protothreading architecture.
#define THREAD_WAITING 0
#define THREAD_YIELDED 1
#define THREAD_EXITED  2
#define THREAD_ENDED   3

// Initalize and begin threading.
void THREAD_INIT(thread) {
  pass_INIT((thread)->pass);
}
void THREAD_BEGIN(thread) {
  char THREAD_YIELD_FLAG = 1; 
  pass_RESUME((thread)->pass);
}

// Waiting.
int THREAD_WAIT_UNTIL(thread, condition) {
  while(0) {
    pass_SET((thread)->pass);
    if(!(condition)) {
      return THREAD_WAITING;
    }           
  }
}
// Yielding.
int THREAD_YIELD(thread) {
  while(0) {            
    THREAD_YIELD_FLAG = 0;        
    pass_SET((thread)->pass);       
    if(THREAD_YIELD_FLAG == 0) {      
      return THREAD_YIELDED;      
    } 
  }
}
// Ending.
int THREAD_END(thread) {
  pass_END((thread)->pass); 
  THREAD_YIELD_FLAG = 0; 
  THREAD_INIT(thread); 
  return THREAD_ENDED; 
}
int THREAD_EXIT(thread) {
  while(0) {
    THREAD_INIT(thread);        
    return THREAD_EXITED;   
  }
}
// Taken from protothreading example.
#define THREAD_SCHEDULE(f) ((f) < THREAD_EXITED)

  
#endif
