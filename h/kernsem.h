#ifndef _KERNSEM_H_
#define _KERNSEM_H_

#include "kernobj.h"
#include "pcblist.h"

class KernelSem : public KernelObj {
public:
	KernelSem(int init = 1) : KernelObj(), val_(init) {}
	~KernelSem() { blocked_.rescheduleAll(); }

	int wait(int toBlock);
	void signal();

	int val() const { return val_; }

private:
	int     val_;
	PCBList blocked_;

	void block();
	void deblock();
};

#endif
