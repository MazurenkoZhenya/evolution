#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

private:
	bool init();

	MainScene();
	~MainScene();

	CREATE_FUNC( MainScene );
};

#endif /*__MAIN_SCENE_H__*/