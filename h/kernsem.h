#ifndef _KERNSEM_H_
#define _KERNSEM_H_

#include "pcblist.h"

class KernelSem {
public:
	KernelSem(int init = 1) : val_(init) {}
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
