//
//  IScene.h
//  MusicalAdventure
//
//  Created by user on 3/27/14.
//  Copyright ampagames 2014. All rights reserved.
//

#ifndef __ISCENE__
#define __ISCENE__

#include "cocos2d.h"
#include "Config.h"

//-----------------------------------------------------------------------------------------------------
class IScene: public cocos2d::CCLayer
{
protected:
	virtual bool	init() = 0;
    virtual void    update(float _dt){};
    
    virtual void    onEnter() = 0;
    virtual void    onExit() = 0;
    
    virtual void    replaceScene(cocos2d::CCScene* _scene) = 0;
    
	virtual			~IScene(){};
};

//-----------------------------------------------------------------------------------------------------
#endif	//__ISCENE__