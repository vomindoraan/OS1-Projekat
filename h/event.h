#ifndef _EVENT_H_
#define _EVENT_H_

#include "ivt.h" // PREPAREENTRY
#include "types.h"

class KernelEvt;

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();

protected:
	void signal();

private:
	KernelEvt* myImpl;
};

#endif
