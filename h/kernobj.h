#ifndef _KERNOBJ_H_
#define _KERNOBJ_H_

#include "types.h"

class KernelObj {
public:
    enum Type {
        THREAD,
        SEMAPHORE,
        EVENT,
    };

    Type type() const { return type_; }
    ID   id()   const { return id_; }

protected:
    KernelObj(Type type) : type_(type), id_(uniqueId_++) {}
    KernelObj(KernelObj const& o) : type_(o.type_), id_(uniqueId_++) {}

    friend class System;

private:
    static ID uniqueId_;

    Type type_;
    ID   id_;
};

#endif
