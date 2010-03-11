#ifndef _HSKEYEDOBJECT_H
#define _HSKEYEDOBJECT_H

#include "plReceiver.h"

/**
 * \brief The base class for any top-level PRP object.
 *
 * Any class that has a unique plKey and can be loaded from a PRP is
 * derived from this class.  hsKeyedObject and plKey go hand-in-hand,
 * and as such, each contains a reference to the other.  For Creatable
 * Class IDs, hsKeyedObject classes will always be in the < 0x0200 range,
 * whereas non-keyed classes are >= 0x0200.
 */
DllClass hsKeyedObject : public plReceiver {
private:
    plKey myKey;

public:
    hsKeyedObject();
    virtual ~hsKeyedObject();

    DECLARE_CREATABLE(hsKeyedObject)

    /**
     * Initializes the key for this KeyedObject with the specified
     * object name.  You will need to either set the location manually
     * or add it to the ResManager for the key's location to be valid.
     * \sa plResManager::AddKey(), plResManager::AddObject()
     */
    void init(const plString& name);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    /** Returns the key that describes this object */
    plKey getKey() const;

    /**
     * Set the object's key.  Most of the time, you will never need to
     * use this directly; you should use init() instead
     * \sa init(), plResManager::AddKey(), plResManager::AddObject()
     */
    void setKey(plKey key);
};

/**
 * \brief Stores the stub of an hsKeyedObject class
 *
 * Like plCreatableStub, this class stores a data buffer containing
 * the contents of an unparsed Creatable.  hsKeyedObjectStub is actually
 * just a convenience class to provide the hsKeyedObject interface to
 * the plCreatableStub, specifically, being able to access the object's
 * key.  If your stub is an hsKeyedObject-derived class, it's very
 * highly recommended you use this instead of a normal plCreatableStub!
 * \sa plCreatableStub
 */
DllClass hsKeyedObjectStub : public hsKeyedObject {
private:
    plCreatableStub* fStub;

public:
    hsKeyedObjectStub();
    virtual ~hsKeyedObjectStub();

    virtual short ClassIndex() const;
    virtual const char* ClassName() const;

    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    /** Returns the underlying plCreatableStub object of this stub */
    const plCreatableStub* getStub() const;

    /** Sets the underlying plCreatableStub object of this stub */
    void setStub(plCreatableStub* stub);
};

#endif
