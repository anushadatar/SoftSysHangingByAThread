#ifndef __THREAD_H__
#define __THREAD_H__

/* 
 *  Define the internal variable of the thread structure.
 */
typedef unsigned short pass_t;
#define PASS_INITALIZE(p) p = 0;
#define PASS_RESUME(p) switch(p) { case 0:
#define PASS_SET(p) p = __LINE__; case __LINE__:
#define PASS_CLEAR(p) }

/* 
 *  Define the thread structure itself.
 */
struct thread {
  pass_t pass;
};

/* Signaling is a useful tool. */
#define THREAD_WAITING 0
#define THREAD_YIELDED 1
#define THREAD_CLOSED  2
#define THREAD_CLEARED 3

/* Definitions for remaining functions. */
#define THREAD_INITALIZE(thread)   PASS_INITALIZE((thread)->pass)
#define THREAD_START(thread) { PASS_RESUME((thread)->pass)

#define THREAD_WAIT_UNTIL(thread, trigger) \
    PASS_SET((thread)->pass); \
    if(!(trigger)) { \
      return THREAD_WAITING; \
    } \

#define THREAD_WAIT_THREAD(thread, child_thread) THREAD_WAIT_UNTIL((thread), !(THREAD_SCHEDULE(child_thread)))

#define THREAD_NEW(thread, child_thread, child) \
    THREAD_INITALIZE((child)); \
    THREAD_WAIT_THREAD((thread), (chiild_thread)); \
    
#define THREAD_SCHEDULE(f) ((f) < THREAD_CLOSED)

#define THREAD_YIELD(thread) \
    THREAD_YIELD = 0; \
    PASS_SET((thread)->pass); \
    if(THREAD_YIELD == 0) { \
      return THREAD_YIELDED; \
    } \
    
#define THREAD_YIELD_UNTIL(thread, trigger) \
    THREAD_YIELD = 0; \
    PASS_SET((thread)->pass); \
    if((THREAD_YIELD == 0) || !(trigger)) { \
      return THREAD_YIELDED; \
    } \

#define THREAD_EXIT(thread) \
    THREAD_INITALIZE(thread); \
    return THREAD_CLOSED; \
    
#define THREAD_CLEAR(thread) \
    PASS_CLEAR((thread)->pass); \
    THREAD_INITALIZE(thread); \
    return THREAD_CLEARED; }
#endif 
