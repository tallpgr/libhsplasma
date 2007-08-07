#ifndef PLSHAREDMESH_H
#define PLSHAREDMESH_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"

class plSharedMesh : public hsKeyedObject {
public:
	hsTArray<plSceneObject const*> fActiveInstances;
    unsigned char fFlags;

public:
	plSharedMesh();
    virtual ~plSharedMesh();

    DECLARE_CREATABLE(plSharedMesh)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
	//virtual bool MsgReceive(plMessage *msg);
};

#endif
