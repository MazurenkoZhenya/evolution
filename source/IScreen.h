//
//  IScreen.h
//  MusicalAdventure
//
//  Created by user on 3/27/14.
//  Copyright ampagames 2014. All rights reserved.
//

#ifndef __ISCREEN__
#define __ISCREEN__

#include "cocos2d.h"
#include "Config.h"

//-----------------------------------------------------------------------------------------------------
class IScreen: public cocos2d::CCLayer
{
protected:
	virtual bool	init() = 0;
    virtual void    update(float _dt){};
    
    virtual void    onEnter() = 0;
    virtual void    onExit() = 0;

	virtual			~IScreen(){};
};

//-----------------------------------------------------------------------------------------------------
#endif	//__ISCREEN__