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


Character::Character()
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

Character* Character::create(string _name)
{
    Character* hero = new Character();
    
    hero->body = CCLayer::create();
    
    hero->name = _name;
    hero->avatar = CCSprite::create("textures/scenes/battle/avatar/icon_1.png");
    hero->avatar->setAnchorPoint(ccp(0, 0));
    
    hero->body->addChild(hero->avatar);    
    return hero;
}