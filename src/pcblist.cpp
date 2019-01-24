#include "pcblist.h"
#include "pcb.h"
#include "locks.h"
#include "schedule.h"

void PCBList::pushBack(PCB* pcb)
{
    LOCKED(
        Node* node = new Node(pcb);
        if (!front_) {
            front_ = node;
        } else {
            back_->next = node;
        }
        back_ = node;
        ++size_;
    )
}

PCB* PCBList::popFront()
{
    LOCKED(
        if (!front_) return NULL;

        PCB* ret = front_->pcb;
        Node* old = front_;
        front_ = front_->next;
        if (!front_) back_ = NULL;

        delete old;
        --size_;
    )
    return ret;
}

void PCBList::rescheduleAll()
{
    LOCKED(
        for (PCB* pcb; pcb = popFront(); pcb->reschedule());
    )
}