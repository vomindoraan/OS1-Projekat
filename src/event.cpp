#include "event.h"
#include "kernevt.h"

Event::Event(IVTNo ivtNo)
{
	LOCKED(
		myImpl = new KernelEvt(ivtNo)
	);
}

Event::~Event()
{
	LOCKED(
		delete myImpl;
	)
}

void Event::wait()
{
	LOCKED(
		myImpl->wait();
	)
}

void Event::signal()
{
	LOCKED(
		myImpl->signal();
	)
}
