//
//  MemoryProfiler.h
//  MusicalAdventure
//
//  Created by madmin on 4/8/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#ifndef __MusicalAdventure__MemoryProfiler__
#define __MusicalAdventure__MemoryProfiler__

#include <iostream>
#include "Cell.h"
#include "Character.h"

class MemoryProfiler
{
public:
    std::vector<Cell*> cellForDell;
    static MemoryProfiler* getInstance();
    static void destroy();
    bool   slogeniya;
private:
    MemoryProfiler();
    ~MemoryProfiler();
    static MemoryProfiler* instance;
};

#endif /* defined(__MusicalAdventure__MemoryProfiler__) */
