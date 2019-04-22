#ifndef _THREAD_H_
#define _THREAD_H_


#ifdef __cplusplus
extern "C"{
#endif
// A thread just contains one
typedef unsigned short pass_t;
typedef struct thread {
  pass_t pass;
} thread;

// Scheduling is hard.

// #define PASS_INIT(s) s = 0;
//
// #define PASS_RESUME(s) switch(s) { case 0:
//
// #define PASS_SET(s) s = __LINE__; case __LINE__:
//
// #define PASS_END(s) };
void PASS_INIT(int s);
void PASS_RESUME(int s);
void PASS_SET(int s);
void PASS_END(int s);
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
