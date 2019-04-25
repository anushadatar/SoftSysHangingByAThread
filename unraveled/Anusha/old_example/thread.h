#ifndef _THREAD_H_
#define __THREAD_H_


#ifdef __cplusplus 
extern "C"{
#endif
// A thread just contains one 
typedef unsigned short pass_t;
typedef struct thread {
  pass_t pass;
} thread;

// Scheduling is hard.
void THREAD_INIT(struct thread* thread);
void THREAD_BEGIN(struct thread* thread);
int THREAD_WAIT_UNTIL(struct thread* thread, int condition);
int THREAD_YIELD(struct thread* thread);
int THREAD_END(struct thread* thread);
int THREAD_EXIT(struct thread* thread); 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

