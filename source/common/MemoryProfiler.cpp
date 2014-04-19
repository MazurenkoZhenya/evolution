//
//  MemoryProfiler.cpp
//  MusicalAdventure
//
//  Created by madmin on 4/8/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#include "MemoryProfiler.h"

MemoryProfiler* MemoryProfiler::instance = NULL;

MemoryProfiler* MemoryProfiler::getInstance()
{
    if(!instance)
    {
        instance = new MemoryProfiler();
    }
    return instance;
}

void MemoryProfiler::destroy()
{
    if(instance)
    {
        instance->cellForDell.clear();
        delete instance;
    }
}

MemoryProfiler::MemoryProfiler()
{
    cellForDell.clear();
}

MemoryProfiler::~MemoryProfiler()
{
    instance = NULL;
}

