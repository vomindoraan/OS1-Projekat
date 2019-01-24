#include "semaphor.h"
#include "locks.h"
#include "kernsem.h"

Semaphore::Semaphore(int init)
{
    LOCKED(
	    myImpl = new KernelSem(init);
    )
}

Semaphore::~Semaphore()
{
    LOCKED(
	    delete myImpl;
    )
}

int Semaphore::wait(int toBlock)
{
    LOCKED(
	    int ret = myImpl->wait(toBlock);
    )
    return ret;
}

void Semaphore::signal()
{
    LOCKED(
	    myImpl->signal();
    )
}

int Semaphore::val() const
{
    LOCKED(
	    int ret = myImpl->val();
    )
    return ret;
}
