#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "idle.h"
#include "kernel.h"
#include "pcb.h"
#include "sleeplst.h"
#include "syscall.h"

class System {
public:
	static PCB*       runningPCB;
	static PCB*       mainPCB;
	static KernelPCB* kernelPCB;
	static IdlePCB*   idlePCB;
	static SleepList* sleepList;

	static void start();
	static void finish();

	static void syscall(Syscall* params);

private:
	System();
	~System();
};

#endif
