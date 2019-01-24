#ifndef _LOCKS_H_
#define _LOCKS_H_

#include "context.h"
#include "types.h"
#include <iostream.h>

extern Word volatile lock;
void dispatch();

#define LOCK      ++lock
#define UNLOCK    if (--lock == 0 && Context::lockTimedOut()) { dispatch(); }
#define LOCKED(s) LOCK; s; UNLOCK;

#define HARD_LOCK      asm { pushf; cli; }
#define HARD_UNLOCK    asm popf
#define HARD_LOCKED(s) HARD_LOCK; s; HARD_UNLOCK;

#endif
