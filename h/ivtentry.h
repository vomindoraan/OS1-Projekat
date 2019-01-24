#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

#include "kernelev.h"
#include "types.h"

class IVTEntry
{
public:
	IVTEntry(IVTNo ivtNo, InterruptRoutine newInterruptRoutine);
	~IVTEntry();
	void signal();
	static IVTEntry * ivtEntries[256];
	InterruptRoutine oldInterruptRoutine, newInterruptRoutine;
	IVTNo ivtNo;
	KernelEv * event;
};


// #define PREPAREENTRY(ivtNo,callOldInterruptRoutine)\
// extern IVTEntry ivtEntry##ivtNo;\
// \
// void interrupt eventInterrupt##ivtNo(){\
// 	if (callOldInterruptRoutine) ivtEntry##ivtNo.oldInterruptRoutine();\
// 	ivtEntry##ivtNo.signal();\
// }\
// \
// IVTEntry ivtEntry##ivtNo(ivtNo,eventInterrupt##ivtNo)

#endif
