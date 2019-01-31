#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include "types.h"

struct Syscall {
	enum Operation {
		_THREAD_MIN = 0x00,
		THREAD_CREATE = _THREAD_MIN,
		THREAD_DESTROY,
		THREAD_START,
		THREAD_WAIT_TO_COMPLETE,
		THREAD_SLEEP,
		_THREAD_MAX,

		_SEMAPHORE_MIN = 0x10,
		SEMAPHORE_CREATE = _SEMAPHORE_MIN,
		SEMAPHORE_DESTROY,
		SEMAPHORE_WAIT,
		SEMAPHORE_SIGNAL,
		SEMAPHORE_VAL,
		_SEMAPHORE_MAX,

		_EVENT_MIN = 0x20,
		EVENT_CREATE = _EVENT_MIN,
		EVENT_DESTROY,
		EVENT_WAIT,
		EVENT_SIGNAL,
		_EVENT_MAX,
	};

	size_t const size;
	Word*        params;

	Syscall(size_t n, Operation op, ...);
	~Syscall();

	friend class System;
};

#endif
