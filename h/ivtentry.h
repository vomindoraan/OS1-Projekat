#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "kernelev.h"
#include "types.h"

class IVTEntry {
public:
	IVTEntry(IVTNo entryNo, InterruptRoutine newRoutine);
	~IVTEntry();

	void signal();
	void callOldInterrupt();
	static IVTEntry* getIVTEntryObjBoundAt(IVTNo entryNum);
private:
	void bindEvent(KernelEv* event);
	void clearEvent();

	IVTNo boundToEntry;
	interruptFunc oldFunc;
	KernelEv* boundKernelEv;
	static IVTEntry* boundEntryObj[256]; //256 ulaza u IV tabelu

	friend class KernelEv;
};

extern volatile int signaledCount;
#define PREPAREENTRY(ENTRY_NO, SHOULD_CALL_OLD) \
	void interrupt AUTOGENINTERRUPT##ENTRY_NO(...); \
	IVTEntry AUTOGENENTRYOBJ##ENTRY_NO((IVTNo)ENTRY_NO, AUTOGENINTERRUPT##ENTRY_NO); \
	void interrupt AUTOGENINTERRUPT##ENTRY_NO(...) { \
		AUTOGENENTRYOBJ##ENTRY_NO.signal(); \
		if(SHOULD_CALL_OLD) \
			AUTOGENENTRYOBJ##ENTRY_NO.callOldInterrupt(); \
		dispatch(); \
	}

#endif
