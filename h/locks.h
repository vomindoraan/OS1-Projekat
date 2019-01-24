#ifndef _LOCKS_H_
#define _LOCKS_H_

#include "context.h"
#include "types.h"

extern int volatile globalLock;
void dispatch();

#define LOCK      globalLock++
#define UNLOCK    if (--globalLock == 0 && Context::timeUp()) { dispatch(); }
#define LOCKED(s) LOCK; s; UNLOCK;

#define HARD_LOCK      asm { pushf; cli; }
#define HARD_UNLOCK    asm popf
#define HARD_LOCKED(s) HARD_LOCK; s; HARD_UNLOCK;

#endif
