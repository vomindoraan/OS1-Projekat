#include "pcb.h"

void PCB::wrapper()
{
    PCB::running->thread_->run();
}
