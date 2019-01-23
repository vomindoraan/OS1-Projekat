#ifndef _LOCKS_H_
#define _LOCKS_H_

#include "types.h"

extern bool globalLock;

#define LOCK()    globalLock = true
#define UNLOCK()  globalLock = false
#define LOCKED(s) LOCK(); s; UNLOCK();

#define MASK()    asm { pushf; cli; }
#define UNMASK()  asm popf
#define MASKED(s) MASK(); s; UNMASK();

#endif
