//
//  Character.h
//  MusicalAdventure
//
//  Created by madmin on 4/7/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#ifndef __MusicalAdventure__Character__
#define __MusicalAdventure__Character__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;
using namespace std;

class Cell;

class Character {
public:
    void                        setName(string _str);
    string                      getName();
    CCLayer*                    getBody();
    static Character*           create(string _name);
    void                        update(float _dt);
    CCSprite*                   avatar;
	float						m_ChanceDropGold;
	float						m_CurCreateCell;
	void						setNewRandomGenerateCell(int _numb);
	float						getCurCreateCell();
	int							getGold();
	float						generateGold(int _num);
private:
	int							m_AddGold;
    Character();
    ~Character();
    CCLayer*			        body;
    string						name;
	float						m_Gold;
};

#endif /* defined(__MusicalAdventure__Character__) */
