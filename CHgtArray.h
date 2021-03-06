/***************************************************************************
 *   Copyright (C) 2006 by Niko V�lim�ki                                   *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef _CHGTARRAY_H_
#define _CHGTARRAY_H_

#include <fstream>
#include "BitRank.h"
#include "CSA.h"

class CHgtArray
{
private:
    ulong n;
    ulong *HgtBits;
    BitRank *Hgt;
    CSA *csa;
    
public:
    CHgtArray(CSA *, const uchar *, ulong);
    CHgtArray(CSA *, const char *);
    ~CHgtArray();
    void SetSA(CSA *);
    void SaveToFile(const char *);
    ulong GetPos(ulong) const;
};

#endif
