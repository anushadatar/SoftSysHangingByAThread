#ifndef __PASS_SWITCH_H__
#define __PASS_SWITCH_H__

/* WARNING! PASS implementation using switch() does not work if an
   PASS_SET() is done within another switch() statement! */

/** \hideinitializer */
typedef unsigned short pass_t;

#define PASS_INIT(s) s = 0;

#define PASS_RESUME(s) switch(s) { case 0:

#define PASS_SET(s) s = __LINE__; case __LINE__:

#define PASS_END(s) }

#endif /* __PASS_SWITCH_H__ */

/** @} */
