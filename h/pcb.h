#ifndef _PCB_H_
#define _PCB_H_

#include "pcblist.h"
#include "schedule.h"
#include "thread.h"
#include "types.h"

class PCB {
public:
	enum State {
		NEW,
		READY,
		RUNNING,
		BLOCKED,
		TERMINATED,
	};

	PCB(Thread* thread, StackSize stackSize, Time timeSlice)
		: thread_(thread), stackSize_(stackSize), timeSlice_(timeSlice)
		, timeLeft_(timeSlice), state_(NEW)
	{}

	~PCB() { waiting_.rescheduleAll(); }

	static void wrapper();
    static PCB* running;

	bool infinite() const { return timeSlice_ == 0; }

	State state() const { return state_; }
	void state(State s) { state_ = s; }

	void reschedule() { state_ = READY; Scheduler::put(this); }

	friend class Context;

private:
	Thread*   thread_;
	StackSize stackSize_;
	Time      timeSlice_;
	Time      timeLeft_;
	State     state_;
	PCBList   waiting_;
};

#endif
