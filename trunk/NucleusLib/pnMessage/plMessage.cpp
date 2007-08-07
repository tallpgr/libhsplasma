#include "plMessage.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

plMessage::plMessage() {
    fSender = new plKey();
}

plMessage::~plMessage() {
    fSender->UnRef();
    for (int i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->UnRef();
}

IMPLEMENT_CREATABLE(plMessage, kMessage, plCreatable)

void plMessage::IMsgRead(hsStream* S) {
    fSender = plResManager::inst->readKey(S);
    fSender->Ref();
    fReceivers.setSize(S->readInt());
    for (int i=0; i<fReceivers.getSize(); i++) {
        fReceivers[i] = plResManager::inst->readKey(S);
        fReceivers[i]->Ref();
    }
    fTimeStamp = S->readDouble();
    fBCastFlags = S->readInt();
}

void plMessage::IMsgWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fSender);
    S->writeInt(fReceivers.getSize());
    for (int i=0; i<fReceivers.getSize(); i++)
        plResManager::inst->writeKey(S, fReceivers[i]);
    S->writeDouble(fTimeStamp);
    S->writeInt(fBCastFlags);
}

