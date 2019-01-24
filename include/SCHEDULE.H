#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

class PCB;

class Scheduler {
public:
	static void put(PCB* pcb);
	static PCB* get();
};

#endif