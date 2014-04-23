//
//  Cell.h
//  MusicalAdventure
//
//  Created by madmin on 4/7/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#ifndef __MusicalAdventure__Cell__
#define __MusicalAdventure__Cell__

#include <iostream>
#include "cocos2d.h"
#include "common/MemoryProfiler.h"

using namespace cocos2d;

class Cell{
public:
    static Cell*    create(int _numberCell);
    CCLayer*        getBody();
    CCSprite*       getRect();
    void            setNumber(int _numberCell);
    int             getNumber();
    ccColor3B       getColor();
    ~Cell();
private:
    Cell();
    CCLabelBMFont*	 number;
    CCSprite*		 rect;
    CCLayer*		 body;
    int				 numberCell;
    ccColor3B		 color;
};

#endif /* defined(__MusicalAdventure__Cell__) */
