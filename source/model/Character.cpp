//
//  Character.cpp
//  MusicalAdventure
//
//  Created by madmin on 4/7/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#include "Character.h"
#include "Cell.h"
#include "BattleScene.h"
#include "math.h"

Character::Character() : 
m_Gold(0),
m_CurCreateCell(0),
m_ChanceDropGold(0),
m_AddGold(5)
{
    
}

Character::~Character()
{
    
}

CCLayer* Character::getBody()
{
    return body;
}

string Character::getName()
{
    return name;
}

void Character::update(float _dt)
{

}

void Character::setName(string _str)
{
    name = _str;
}

void Character::setNewRandomGenerateCell(int _numb)
{
	m_CurCreateCell = _numb;
	m_ChanceDropGold = (log10(m_CurCreateCell) / log10(2)) * 5;
}

float Character::getCurCreateCell()
{
	return m_CurCreateCell;
}

int Character::getAddGol()
{
	return m_AddGold;
}

float Character::generateGold(int _num)
{
	float gen = 0;

	if(rand()%100 < m_ChanceDropGold)
		gen = rand()%(m_AddGold * static_cast<int>(log10(_num) / log10(2)));

	m_Gold += gen;
	return gen;
}

Character* Character::create(string _name)
{
    Character* hero = new Character();
    
    hero->body = CCLayer::create();
    hero->name = _name;
    hero->avatar = CCSprite::create();
    hero->avatar->setAnchorPoint(ccp(0, 0));

	hero->setNewRandomGenerateCell(2);

    hero->body->addChild(hero->avatar);    
    return hero;
}