#ifndef _PCB_H_
#define _PCB_H_

#include "locks.h"
#include "pcblist.h"
#include "schedule.h"
#include "thread.h"
#include "types.h"
#include <stdlib.h>

class PCB {
public:
	enum State {
		NEW,
		READY,
		RUNNING,
		BLOCKED,
		TERMINATED,
	};

	static StackSize const MAX_STACK_SIZE;
	static PCB* running;

	PCB(StackSize stackSize, Time timeSlice, Thread* thread = NULL);
	~PCB();

	Thread*   thread()     const { return thread_; }
	StackSize stackCount() const { return stackCount_; }
	Time      timeSlice()  const { return timeSlice_; }

	State state()        const { return state_; }
	void  state(State s)       { state_ = s; }

	bool infinite() const { return timeSlice_ == 0; }

	void reschedule() { LOCKED(state_ = READY; Scheduler::put(this)); }

	void waitToComplete();

	friend class Context;

protected:
	void initializeStack(WrapperFunc wrapper);

private:
	Thread* thread_;

	// Stack data
	StackSize         stackCount_;
	Word*             stack_;
	Register volatile ss_, sp_, bp_;

	// Time sharing data
	Time  timeSlice_;
	Time  timeLeft_;
	State state_;
	Word  savedLock_;

	// Wait/sleep data
	PCBList waiting_;

	static void threadWrapper();
};

#endif
