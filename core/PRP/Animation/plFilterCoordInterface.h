/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLFILTERCOORDINTERFACE_H
#define _PLFILTERCOORDINTERFACE_H

#include "PRP/Object/plCoordinateInterface.h"

class PLASMA_DLL plFilterCoordInterface : public plCoordinateInterface {
    CREATABLE(plFilterCoordInterface, kFilterCoordInterface,
              plCoordinateInterface)

public:
    enum {
        kNoRotation = 0x1,
        kNoTransX = 0x2,
        kNoTransY = 0x4,
        kNoTransZ = 0x8,
        kNoMove = kNoTransX | kNoTransY | kNoTransZ,
        kNoNothing = kNoMove | kNoRotation
    };

protected:
    unsigned int fFilterMask;
    hsMatrix44 fRefParentLocalToWorld;

public:
    plFilterCoordInterface() : fFilterMask(0) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
