#ifndef _PCBLIST_H_
#define _PCBLIST_H_

#include "pcb.h"

class PCBList {
public:
    PCBList() {}
    ~PCBList() { while (popFront()); }

    PCB* front() const { return front_->pcb; }
    PCB* back()  const { return back_->pcb; }

    void pushBack(PCB* pcb);
    PCB* popFront();

    void rescheduleAll();

private:
    struct Node {
        PCB* pcb;
        Node* next;

        Node(PCB* pcb, Node* next = NULL) : pcb(pcb), next(next) {}
    };

    Node*    front_ = NULL;
    Node*    back_  = NULL;
    unsigned size_  = 0;
};

#endif
