//
//  MemoryProfiler.cpp
//  MusicalAdventure
//
//  Created by madmin on 4/8/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#include "MemoryProfiler.h"
#include <cmath>

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

MemoryProfiler::MemoryProfiler() :
slogeniya(false),
START_POS_ARR(ccp(70, 690)),
m_DefSize(4),
m_Size(4),
m_Scale(1.0f),
INDENT_CELL(ccp(25, 25))//12, 13))
{
	m_Scale = (637.0f / ((m_Size - m_DefSize) * 153.0f + 637.0f));
	cellForDell.clear();
}

void MemoryProfiler::setSize(int _size)
{
	m_Size = _size;
	m_Scale = (637.0f / ((m_Size - m_DefSize) * 153.0f + 637.0f));
}

MemoryProfiler::~MemoryProfiler()
{
    instance = NULL;
}