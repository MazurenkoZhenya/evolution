#pragma once

#include "cocos2d.h"

class ShopScene: public cocos2d::CCLayer
{

public:   
    static cocos2d::CCScene*			scene();

	CREATE_FUNC(ShopScene);

private:
	
    bool								init();
    //void								update(float _dt);
		
	
private:
	ShopScene(void);
	~ShopScene(void);
};

