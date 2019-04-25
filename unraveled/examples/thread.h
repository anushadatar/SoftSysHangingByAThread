/*
 * Copyright (c) 2004-2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: pt.h,v 1.6 2006/06/03 11:29:43 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \file
 * Protothreads implementation.
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include "pass.h"

struct thread {
  pass_t pass;
};

#define THREAD_WAITING 0
#define THREAD_EXITED  1
#define THREAD_ENDED   2
#define THREAD_YIELDED 3

/**
 * \name Initialization
 * @{
 */

/**
 * Initialize a protothread.
 *
 * Initializes a protothread. Initialization must be done prior to
 * starting to execute the protothread.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define THREAD_INIT(thread)   PASS_INIT((thread)->pass)

/** @} */

/**
 * \name Declaration and definition
 * @{
 */

/**
 * Declaration of a protothread function.
 *
 * This macro is used to declare a protothread function. Protothreads
 * function should be declared with this macro, but can also be
 * declared as regular C functions that return an integer value.
 *
 * \param name_args The name and arguments of the C function
 * implementing the protothread.
 *
 * \hideinitializer
 */
#define THREAD_THREAD(name_args) char name_args

/**
 * Declare the start of a protothread inside the C function
 * implementing the protothread.
 *
 * This macro is used to declare the starting point of a
 * protothread. It should be placed at the start of the function in
 * which the protothread runs. All C statements above the PT_BEGIN()
 * invokation will be executed each time the protothread is scheduled.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define THREAD_BEGIN(thread) { char THREAD_YIELD_FLAG = 1; PASS_RESUME((thread)->pass)

/**
 * Declare the end of a protothread.
 *
 * This macro is used for declaring that a protothread ends. It must
 * always be used together with a matching PT_BEGIN() macro.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define THREAD_END(thread) PASS_END((thread)->pass); THREAD_YIELD_FLAG = 0; \
                   THREAD_INIT(thread); return THREAD_ENDED; }

/** @} */

/**
 * \name Blocked wait
 * @{
 */

/**
 * Block and wait until condition is true.
 *
 * This macro blocks the protothread until the specified condition is
 * true.
 *
 * \param pt A pointer to the protothread control structure.
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define THREAD_WAIT_UNTIL(thread, condition)	        \
  do {						\
    PASS_SET((thread)->pass);				\
    if(!(condition)) {				\
      return THREAD_WAITING;			\
    }						\
  } while(0)

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * PT_WAIT_UNTIL().
 *
 * \param pt A pointer to the protothread control structure.
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define THREAD_WAIT_WHILE(thread, cond)  THREAD_WAIT_UNTIL((thread), !(cond))

/** @} */

/**
 * \name Hierarchical protothreads
 * @{
 */

/**
 * Block and wait until a child protothread completes.
 *
 * This macro schedules a child protothread. The current protothread
 * will block until the child protothread completes.
 *
 * \note The child protothread must be manually initialized with the
 * PT_INIT() function before this function is used.
 *
 * \param pt A pointer to the protothread control structure.
 * \param thread The child protothread with arguments
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define THREAD_WAIT_THREAD(thread, thread2) PTHREADWAIT_WHILE((thread), THREAD_SCHEDULE(thread2))

/**
 * Spawn a child protothread and wait until it exits.
 *
 * This macro spawns a child protothread and waits until it exits. The
 * macro can only be used within a protothread.
 *
 * \param pt A pointer to the protothread control structure.
 * \param child A pointer to the child protothread's control structure.
 * \param thread The child protothread with arguments
 *
 * \hideinitializer
 */
#define THREAD_SPAWN(thread, child, thread2)		\
  do {						\
    THREAD_INIT((child));				\
    THREAD_WAIT_THREAD((thread), (thread2));		\
  } while(0)

/** @} */

/**
 * \name Exiting and restarting
 * @{
 */

/**
 * Restart the protothread.
 *
 * This macro will block and cause the running protothread to restart
 * its execution at the place of the PT_BEGIN() call.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define THREAD_RESTART(thread)				\
  do {						\
    THREAD_INIT(thread);				\
    return THREAD_WAITING;			\
  } while(0)

/**
 * Exit the protothread.
 *
 * This macro causes the protothread to exit. If the protothread was
 * spawned by another protothread, the parent protothread will become
 * unblocked and can continue to run.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define THREAD_EXIT(thread)				\
  do {						\
    THREAD_INIT(thread);				\
    return THREAD_EXITED;			\
  } while(0)

/** @} */

/**
 * \name Calling a protothread
 * @{
 */

/**
 * Schedule a protothread.
 *
 * This function shedules a protothread. The return value of the
 * function is non-zero if the protothread is running or zero if the
 * protothread has exited.
 *
 * \param f The call to the C function implementing the protothread to
 * be scheduled
 *
 * \hideinitializer
 */
#define THREAD_SCHEDULE(f) ((f) == THREAD_WAITING)

/** @} */

/**
 * \name Yielding from a protothread
 * @{
 */

/**
 * Yield from the current protothread.
 *
 * This function will yield the protothread, thereby allowing other
 * processing to take place in the system.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define THREAD_YIELD(thread)				\
  do {						\
    THREAD_YIELD_FLAG = 0;				\
    PASS_SET((thread)->pass);				\
    if(THREAD_YIELD_FLAG == 0) {			\
      return THREAD_YIELDED;			\
    }						\
  } while(0)

/**
 * \brief      Yield from the protothread until a condition occurs.
 * \param pt   A pointer to the protothread control structure.
 * \param cond The condition.
 *
 *             This function will yield the protothread, until the
 *             specified condition evaluates to true.
 *
 *
 * \hideinitializer
 */
#define THREAD_YIELD_UNTIL(thread, cond)		\
  do {						\
    THREAD_YIELD_FLAG = 0;				\
    PASS_SET((thread)->pass);				\
    if((THREAD_YIELD_FLAG == 0) || !(cond)) {	\
      return THREAD_YIELDED;			\
    }						\
  } while(0)

/** @} */

#endif /* __PT_H__ */

/** @} */





// #ifndef _THREAD_H_
// #define _THREAD_H_
//
//
// #ifdef __cplusplus
// extern "C"{
// #endif
//
//
// #include "pass.h"
// // A thread just contains one
// // typedef unsigned short pass_t;
// typedef struct thread {
//   pass_t pass;
// } thread;
//
// // Scheduling is hard.
//
// // #define PASS_INIT(s) s = 0;
// //
// // #define PASS_RESUME(s) switch(s) { case 0:
// //
// // #define PASS_SET(s) s = __LINE__; case __LINE__:
// //
// // #define PASS_END(s) };
// // void PASS_INIT(int s);
// // void PASS_RESUME(int s);
// // void PASS_SET(int s);
// // void PASS_END(int s);
// void THREAD_INIT(struct thread* thread);
// void THREAD_BEGIN(struct thread* thread);
// int THREAD_WAIT_UNTIL(struct thread* thread, int condition);
// int THREAD_YIELD(struct thread* thread);
// int THREAD_END(struct thread* thread);
// int THREAD_EXIT(struct thread* thread);
//
// #ifdef __cplusplus
// } // extern "C"
// #endif
//
//
// #endif
