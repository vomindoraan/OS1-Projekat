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
	void signal();

private:
	KernelEv* myImpl;
};

#endif
