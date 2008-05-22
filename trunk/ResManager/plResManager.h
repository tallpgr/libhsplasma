#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "PRP/KeyedObject/plLocation.h"
#include "pdUnifiedTypeMap.h"
#include "Stream/plEncryptedStream.h"
#include "Util/hsTArray.hpp"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include "plKeyCollector.h"
#include "PRP/plPageInfo.h"
#include "plAgeInfo.h"

DllClass plResManager /* : public hsResMgr */ {
private:
    static unsigned int fNumResMgrs;

protected:
    PlasmaVer fPlasmaVer;
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeInfo*> ages;

private:
    void ReadKeyring(hsStream* S, const plLocation& loc);
    unsigned int ReadObjects(hsStream* S, const plLocation& loc);
    void WriteKeyring(hsStream* S, const plLocation& loc);
    unsigned int WriteObjects(hsStream* S, const plLocation& loc);

public:
    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    void setVer(PlasmaVer pv, bool force = false);
    PlasmaVer getVer();

    plKey readKey(hsStream* S);
    plKey readUoid(hsStream* S);
    void writeKey(hsStream* S, plKey key);
    void writeKey(hsStream* S, hsKeyedObject* ko);
    void writeUoid(hsStream* S, plKey key);
    void writeUoid(hsStream* S, hsKeyedObject* ko);
    plKey prcParseKey(const pfPrcTag* tag);
    class hsKeyedObject* getObject(const plKey& key);
    unsigned int countKeys(const PageID& pid);

    plPageInfo* ReadPage(const char* filename);
    void WritePage(const char* filename, plPageInfo* page);
    void WritePrc(pfPrcHelper* prc, plPageInfo* page);
    void UnloadPage(const plLocation& loc);
    void UnloadPage(const char* ageName, const char* pageName);
    
    plAgeInfo* ReadAge(const char* filename);
    void WriteAge(const char* filename, plAgeInfo* age);
    void UnloadAge(plAgeInfo* age);

    class plCreatable* ReadCreatable(hsStream* S);
    void WriteCreatable(hsStream* S, class plCreatable* pCre);
    class plCreatable* prcParseCreatable(const pfPrcTag* tag);

    class plSceneNode* getSceneNode(const plLocation& loc);
    std::vector<plLocation> getLocations();
    std::vector<short> getTypes(const plLocation& loc);
    std::vector<plKey> getKeys(const plLocation& loc, short type);
};

#endif

