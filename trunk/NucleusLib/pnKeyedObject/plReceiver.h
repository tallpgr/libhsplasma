#ifndef _PLRECEIVER_H
#define _PLRECEIVER_H

#include "../pnFactory/plCreatable.h"
#include "../pnMessage/plMessage.h"
#include "plKey.h"

DllClass plReceiver : public plCreatable {
public:
    plReceiver();
    virtual ~plReceiver();

    DECLARE_CREATABLE(plReceiver)

    virtual bool msgReceive(plMessage* msg);
};

#endif
