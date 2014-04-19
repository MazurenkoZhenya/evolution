//
//  Cell.cpp
//  MusicalAdventure
//
//  Created by madmin on 4/7/14.
//  Copyright (c) 2014 ampagames. All rights reserved.
//

#include "Cell.h"

Cell::Cell()
{
    
}

Cell::~Cell()
{
    
}

Cell* Cell::create(int _numberCell)
{
    Cell* cell = new Cell();
    char buf[255];
    sprintf(buf, "%d", _numberCell);
    
    cell->numberCell = _numberCell;
    cell->rect = CCSprite::create("textures/2048/cell.png");
    cell->rect->setAnchorPoint(ccp(0, 1));
    
    cell->number = CCLabelBMFont::create(buf, "fonts/days26black.fnt", 35);
    cell->number->setPosition(ccp(cell->rect->getContentSize().width / 2, cell->rect->getContentSize().height / 2));
    cell->number->setColor(ccBLACK);
    cell->rect->addChild(cell->number);
    
    cell->body = CCLayer::create();
    cell->body->addChild(cell->rect);
    cell->body->setAnchorPoint(ccp(0, 0));
    //cell->body->setRotation(90);
    
    ccColor3B color;
    color.r = 232;
    color.g = 233;
    color.b = 236;
    cell->rect->setColor(color);
    cell->color = color;
    
    return cell;
}

CCLayer* Cell::getBody()
{
    return body;
}

CCSprite* Cell::getRect()
{
    return rect;
}

int Cell::getNumber()
{
    return numberCell;
}

void Cell::setNumber(int _numberCell)
{
    numberCell = _numberCell;
    
    if(color.r > 0)
    {
        color.r -= 14;
        color.g -= 12;
        color.b -= 7;
    }
    
    this->rect->setColor(color);
    
    char buf[255];
    sprintf(buf, "%d", numberCell);
    number->setString(buf);
}

void Cell::setPos(CCPoint _pos)
{
    pos = _pos;
}
CCPoint& Cell::getPos()
{
    return pos;
}

ccColor3B Cell::getColor()
{
    return color;
}