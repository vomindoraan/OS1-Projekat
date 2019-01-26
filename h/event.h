#ifndef _EVENT_H_
#define _EVENT_H_

#include "ivt.h" // PREPAREENTRY
#include "types.h"

class KernelEv;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	void signal(); // can call KernelEv

	friend class KernelEv;

private:
	KernelEv* myImpl;
};

#endif
