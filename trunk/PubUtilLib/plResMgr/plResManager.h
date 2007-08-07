#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../PlasmaDefs.h"
#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../PubUtilLib/plScene/plSceneNode.h"
#include "../../CoreLib/plEncryptedStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"
#include "plKeyCollector.h"
#include "plPageInfo.h"
#include "plPageSettings.h"

DllClass plResManager /* : public hsResMgr */ {
protected:
    PlasmaVer ver;
    static int resManagers;

public:
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeSettings*> ages;

private:
    plKey* readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey* key);
    void ReadKeyring(hsStream* S, plLocation& loc);
    unsigned int ReadObjects(hsStream* S, plLocation& loc);
    void WriteKeyring(hsStream* S, plLocation& loc);
    unsigned int WriteObjects(hsStream* S, plLocation& loc);

public:
    static plResManager* inst;

    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    virtual void setVer(PlasmaVer pv, bool mutate = false);
    PlasmaVer getVer();

    plKey* readKey(hsStream* S);
    plKey* readUoidKey(hsStream* S);
    void writeKey(hsStream* S, plKey* key);
    void writeKey(hsStream* S, hsKeyedObject* ko);
    void writeUoidKey(hsStream* S, plKey* key);
    void writeUoidKey(hsStream* S, hsKeyedObject* ko);
    hsKeyedObject* getObject(plKey& key);

    plPageInfo* ReadPage(const char* filename);
    void WritePage(const char* filename, plPageInfo* page);
    void WritePrc(pfPrcHelper* prc, plPageInfo* page);
    void UnloadPage(plLocation& loc);
    
    plAgeSettings* ReadAge(const char* filename);
    void WriteAge(const char* filename, plAgeSettings* age);
    void UnloadAge(plAgeSettings* age);

    plCreatable* ReadCreatable(hsStream* S);
    void WriteCreatable(hsStream* S, plCreatable* pCre);

    plSceneNode* getSceneNode(plLocation& loc);
};

#endif

